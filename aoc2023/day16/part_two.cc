module;

#include <algorithm>
#include <cstdint>
#include <queue>
#include <ranges>
#include <span>
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
};
struct Beam {
  Coord position;
  Coord direction;
  auto operator<=>(const Beam &) const = default;
};
} // namespace

template <> struct std::hash<Coord> {
  std::size_t operator()(const Coord &c) const noexcept {
    std::size_t h1 = std::hash<int64_t>{}(c.row);
    std::size_t h2 = std::hash<int64_t>{}(c.row);
    return h1 ^ (h2 << 1);
  }
};

template <> struct std::hash<Beam> {
  std::size_t operator()(const Beam &b) const noexcept {
    std::size_t h1 = std::hash<Coord>{}(b.position);
    std::size_t h2 = std::hash<Coord>{}(b.direction);
    return h1 ^ (h2 << 1);
  }
};

namespace {
int64_t energize(std::span<std::string_view> grid, Coord pos, Coord dir) {
  std::queue<Beam> q;
  std::unordered_set<Beam> visited;
  std::unordered_set<Coord> energized;

  // Helper to check whether a Beam location is valid
  auto can_step = [&](const Beam &beam) {
    // Within bounds
    if (beam.position.row < 0 || beam.position.col < 0)
      return false;
    if (beam.position.row >= std::ssize(grid))
      return false;
    if (beam.position.col >= std::ssize(grid[0]))
      return false;
    // Not yet visited
    return not visited.contains(beam);
  };

  q.push(Beam{pos, dir});
  visited.insert(Beam{pos, dir});
  energized.insert(pos);

  // Helper that does one step in the given direction
  auto step = [&](Coord pos, Coord dir) {
    if (can_step(Beam{pos + dir, dir})) {
      visited.insert(Beam{pos + dir, dir});
      q.push(Beam{pos + dir, dir});
      energized.insert(pos + dir);
    }
  };

  while (not q.empty()) {
    auto [pos, dir] = q.front();
    q.pop();

    switch (grid[pos.row][pos.col]) {
    case '.':
      // Empty space, continue forward
      step(pos, dir);
      break;
    case '-':
      // Edge-on, continue forward
      if (dir.row == 0) {
        step(pos, dir);
      } else {
        // Hitting the splitter, split
        step(pos, {0, -1});
        step(pos, {0, 1});
      }
      break;
    case '|':
      // Edge-on, continue forward
      if (dir.col == 0) {
        step(pos, dir);
      } else {
        // Hitting the splitter, split
        step(pos, {1, 0});
        step(pos, {-1, 0});
      }
      break;
    case '/':
      // 90 degree turn
      step(pos, {-dir.col, -dir.row});
      break;
    case '\\':
      // 90 degree turn
      step(pos, {dir.col, dir.row});
      break;
    }
  }

  return energized.size();
}
} // namespace

export namespace part_two {
int64_t energized_from_sides(std::string_view map) {
  std::vector<std::string_view> grid;
  std::ranges::copy(
      map | std::views::split('\n') |
          std::views::transform([](auto rng) { return std::string_view(rng); }),
      std::back_inserter(grid));

  // Iterate over all the starting positions
  int64_t max = 0;
  for (int64_t col = 0; col < std::ssize(grid[0]); ++col) {
    if (col == 0)
      max = std::max(max, energize(grid, {0, col}, {0, 1}));
    if (col == std::ssize(grid[0]) - 1)
      max = std::max(max, energize(grid, {0, col}, {0, -1}));
    max = std::max(max, energize(grid, {0, col}, {1, 0}));
  }

  return max;
}
} // namespace part_two