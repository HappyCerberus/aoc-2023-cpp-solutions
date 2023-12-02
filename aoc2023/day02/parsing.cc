module;

#include <iostream>
#include <unordered_map>

export module parsing;

export namespace parsing {
struct Marble {
  enum Type { RED, GREEN, BLUE } type;
  int64_t count;
  friend std::istream &operator>>(std::istream &s, Marble &marble);
};

struct Game {
  int64_t id;
  std::unordered_map<Marble::Type, int64_t> max;
  friend std::istream &operator>>(std::istream &s, Game &game);
  int64_t power() const;
};
} // namespace parsing

namespace parsing {
int64_t Game::power() const {
  return max.at(Marble::RED) * max.at(Marble::GREEN) * max.at(Marble::BLUE);
}

std::istream &operator>>(std::istream &s, Game &game) {
  if (s.peek() != 'G' || not s.ignore(5)) {
    // Peeking does not set a fail flag, we have to do that manually
    s.setstate(std::ios_base::failbit);
    return s;
  }
  if (not(s >> game.id))
    return s;
  s.ignore(1); // ':'

  // We have a game, now read the sets of marbles.
  game.max.clear();
  Marble marble;
  while (s >> marble) {
    game.max[marble.type] = std::max(game.max[marble.type], marble.count);

    auto delim = s.get();
    // Next marble or set of marbles (it actually doesn't matter)
    if (delim == ',' || delim == ';')
      continue;
    // End of this game
    if (delim == '\n')
      break;
    // End of input
    if (delim == std::char_traits<char>::eof()) {
      // This is the last game, we need to clear the eof flag, otherwise it
      // would be ignored. We want the failure to be detected when we attempt
      // reading the next game.
      s.clear();
      break;
    }
  }
  return s;
}

std::istream &operator>>(std::istream &s, Marble &marble) {
  // Number of marbles
  if (not(s >> marble.count))
    return s;

  // Ignore whitespace
  while (s.peek() == ' ')
    s.get();

  // Based on the first letter set the color and ignore the appropriate
  // number of characters.
  switch (s.peek()) {
  case 'b':
    marble.type = Marble::BLUE;
    s.ignore(4);
    break;
  case 'g':
    marble.type = Marble::GREEN;
    s.ignore(5);
    break;
  case 'r':
    marble.type = Marble::RED;
    s.ignore(3);
    break;
  default:
    throw std::runtime_error("Parsing error, unexpected color.");
  }
  return s;
}
} // namespace parsing