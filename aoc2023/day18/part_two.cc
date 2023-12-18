module;

#include <algorithm>
#include <cassert>
#include <charconv>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <ranges>
#include <set>
#include <span>
#include <spanstream>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

export module part_two;

namespace {
struct Coord {
  int64_t row;
  int64_t col;
  auto operator<=>(const Coord &) const = default;
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
};
struct Instruction {
  Coord dig;
  int64_t distance;
  friend std::istream &operator>>(std::istream &s, Instruction &instr) {
    std::string skip;
    if (not(s >> skip >> skip))
      return s;
    std::string instruction;
    s >> instruction;
    std::from_chars(instruction.c_str() + 2, instruction.c_str() + 7,
                    instr.distance, 16);

    switch (instruction[7]) {
    case '0':
      instr.dig = {0, 1};
      break;
    case '1':
      instr.dig = {1, 0};
      break;
    case '2':
      instr.dig = {0, -1};
      break;
    case '3':
      instr.dig = {-1, 0};
      break;
    }
    return s;
  }
};
struct Wall {
  Coord top_left;
  Coord bottom_right;
  Wall(Coord a, Coord b)
      : top_left(std::min(a, b)), bottom_right(std::max(a, b)) {}
  bool is_horizontal() const { return top_left.row == bottom_right.row; }
  bool is_single() const { return top_left == bottom_right; }
  bool operator<(const Wall &other) const {
    // Special sorting to keep horizontal walls in-between the two vertical
    // walls in our order
    if (top_left == other.top_left) {
      if (is_single() && not other.is_single())
        return true;
      if (not is_horizontal() && other.is_horizontal())
        return true;
      return false;
    }
    return top_left < other.top_left;
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

export namespace part_two {
int64_t big_lagoon_size(std::span<const char> instructions) {
  std::ispanstream s(instructions);

  // Parse out the walls
  std::multiset<Wall> walls;
  Coord current{0, 0};
  for (const auto &dig : std::views::istream<Instruction>(s)) {
    auto next = current + dig.dig * dig.distance;
    walls.insert(Wall{current, next});
    current = next;
  }

  // Calculate the size of the perimeter
  int64_t perimeter =
      std::ranges::fold_left(walls, 0z, [](int64_t acc, Wall wall) {
        return acc + (wall.bottom_right.row - wall.top_left.row) +
               (wall.bottom_right.col - wall.top_left.col);
      });

  int64_t inside = 0;

  while (not walls.empty()) {
    // Grab a range that spans all lines that are on the current row
    auto begin = walls.begin();
    Wall tail{Coord{walls.begin()->top_left.row + 1, INT64_MIN},
              {INT64_MAX, INT64_MAX}};
    auto end = walls.upper_bound(tail);

    int64_t inside_spaces = 0;
    int64_t line_count = 0;
    Wall prev{{0, 0}, {0, 0}};
    for (auto it = begin; it != end; ++it) {
      // If we are looking at a horizontal line, adjust the count of lines to
      // the left accordingly to the shape
      if (it != begin && std::prev(it)->top_left.col == it->top_left.col) {
        // Check the shape
        auto before = std::prev(it);
        auto after = std::next(it);
        // Closed shape, U or A
        if ((before->is_single() && after->is_single()) ||
            (not before->is_single() && not after->is_single()))
          --line_count;
      } else {
        // If we have odd number of lines to the left, we can calculate the
        // number of spaces from the previous line to the left
        if (line_count % 2 == 1)
          inside_spaces +=
              std::max(it->top_left.col - prev.bottom_right.col - 1, 0z);
      }
      // Every line counts
      ++line_count;
      prev = *it;
    }

    // Now we need to calculate how many number of rows will the number of
    // inside spaces remain the same

    // Start on the current row
    int64_t first_row = walls.begin()->top_left.row;
    // Grab the first ending line
    int64_t last_row = std::ranges::min(std::ranges::subrange(begin, end),
                                        std::less<>{}, &Wall::bottom_right)
                           .bottom_right.row;
    // If the next line in the datastructure starts before of the lines ends
    if (end != walls.end())
      last_row = std::min(last_row, end->top_left.row);
    // Horizontal lines end on the same line, but we want to always at least
    // advance once
    last_row = std::max(first_row + 1, last_row);
    // Calculate the total number of inside spaces
    inside += inside_spaces * (last_row - first_row);

    // Now we need to modify the lines. We either remove them, or truncate them
    // so they start on the one line after last_row.
    while (not walls.empty() && walls.begin()->top_left.row == first_row) {
      if (walls.begin()->is_horizontal()) {
        walls.erase(walls.begin());
        continue;
      }
      // Because we are working with std::set, we cannot modify the value
      // in-place
      auto node = walls.extract(walls.begin());
      node.value().top_left.row = last_row;
      walls.insert(std::move(node));
    }
  }

  return inside + perimeter;
}
} // namespace part_two