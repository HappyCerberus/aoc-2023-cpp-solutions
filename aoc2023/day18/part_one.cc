module;

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <ranges>
#include <span>
#include <spanstream>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

export module part_one;

namespace {
struct Coord {
  int64_t row;
  int64_t col;
  Coord operator+(const Coord &other) const {
    Coord result = *this;
    result.row += other.row;
    result.col += other.col;
    return result;
  }
  Coord operator*(int64_t scalar) const {
    Coord result = *this;
    result.row *= scalar;
    result.col *= scalar;
    return result;
  }
  auto operator<=>(const Coord &) const = default;
};
struct Instruction {
  Coord dig;
  int64_t distance;
  friend std::istream &operator>>(std::istream &s, Instruction &instr) {
    while (std::isspace(s.peek()))
      s.ignore();
    switch (s.get()) {
    case 'U':
      instr.dig = {-1, 0};
      break;
    case 'D':
      instr.dig = {1, 0};
      break;
    case 'L':
      instr.dig = {0, -1};
      break;
    case 'R':
      instr.dig = {0, 1};
      break;
    }
    s >> instr.distance;
    std::string colour;
    return s >> colour;
  }
};
} // namespace

template <> struct std::hash<Coord> {
  std::size_t operator()(const Coord &c) const noexcept {
    std::size_t h1 = std::hash<int64_t>{}(c.row);
    std::size_t h2 = std::hash<int64_t>{}(c.row);
    return h1 ^ (h2 << 1);
  }
};

export namespace part_one {
int64_t lagoon_size(std::span<const char> instructions) {
  Coord top_left{0, 0}, bottom_right{0, 0};
  std::unordered_set<Coord> dug_out;

  Coord current{0, 0};
  std::ispanstream s(instructions);
  for (const auto &dig : std::views::istream<Instruction>(s)) {
    // The end of the current wall
    auto next = current + dig.dig * dig.distance;

    // Keep track of the bounding box
    top_left.row = std::min(top_left.row, next.row);
    top_left.col = std::min(top_left.col, next.col);
    bottom_right.row = std::max(bottom_right.row, next.row);
    bottom_right.col = std::max(bottom_right.col, next.col);

    // Dig out the wall
    do {
      current = current + dig.dig;
      dug_out.insert(current);
    } while (current != next);
  }

  std::unordered_set<Coord> outside;
  // Expand the bounding box by one space on each side
  --top_left.row;
  --top_left.col;
  ++bottom_right.row;
  ++bottom_right.col;

  // BFS search for spaces reachable from the outside
  std::queue<Coord> q;
  q.push(top_left);
  outside.insert(top_left);

  // Helper that checks for out of bound, visited spaces and walls
  auto can_step = [&](Coord coord) {
    if (coord.row < top_left.row)
      return false;
    if (coord.col < top_left.col)
      return false;
    if (coord.row > bottom_right.row)
      return false;
    if (coord.col > bottom_right.col)
      return false;
    return not(outside.contains(coord) || dug_out.contains(coord));
  };

  while (not q.empty()) {
    auto current = q.front();
    q.pop();
    // Iterate over all directions
    for (auto dir : {Coord{-1, 0}, Coord{1, 0}, Coord{0, -1}, Coord{0, 1}}) {
      if (not can_step(current + dir))
        continue;
      outside.insert(current + dir);
      q.push(current + dir);
    }
  }

  return (bottom_right.row - top_left.row + 1) *
             (bottom_right.col - top_left.col + 1) -
         outside.size();
}
} // namespace part_one