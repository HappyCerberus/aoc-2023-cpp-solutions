module;

#include <iostream>
#include <unordered_map>
#include <vector>

export module graph;

export namespace graph {
struct Graph {
  enum Direction { Left, Right };
  std::string &step(const std::string &state, Direction direction) {
    if (direction == Left)
      return map[state].first;
    else // if (direction == Right)
      return map[state].second;
  }

  friend std::istream &operator>>(std::istream &s, Graph &graph) {
    auto drop_irrelevant = [&] {
      while (s && not std::isupper(s.peek()))
        s.ignore();
    };
    auto read_location = [&] {
      auto get = [&] { return static_cast<char>(s.get()); };
      return std::string{get(), get(), get()};
    };
    while (not s.eof()) {
      drop_irrelevant();
      std::string key = read_location();
      drop_irrelevant();
      std::string left = read_location();
      drop_irrelevant();
      std::string right = read_location();
      graph.map[key] = std::pair{left, right};
      // Is this a starting position?
      if (key[2] == 'A')
        graph.start.push_back(key);
      drop_irrelevant();
    }
    return s;
  }

  std::vector<std::string> start;
  std::unordered_map<std::string, std::pair<std::string, std::string>> map;
};
} // namespace graph