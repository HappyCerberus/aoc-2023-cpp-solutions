module;

#include <algorithm>
#include <cstdint>
#include <deque>
#include <functional>
#include <ranges>
#include <set>
#include <span>
#include <string>
#include <unordered_set>
#include <vector>

export module part_one;

namespace {
struct Coord {
  int64_t row;
  int64_t col;
  auto operator<=>(const Coord &) const = default;
};
} // namespace

template <> struct std::hash<Coord> {
  std::size_t operator()(const Coord &c) const noexcept {
    std::size_t h1 = std::hash<int64_t>{}(c.row);
    std::size_t h2 = std::hash<int64_t>{}(c.col);
    return h1 ^ (h2 << 1);
  }
};

namespace {
int64_t max_path(std::span<std::string_view> map, Coord start, Coord exit) {
  std::unordered_set<Coord> visited;
  std::vector<std::tuple<Coord, int64_t, int64_t>> dfs;

  // std::function as a workaround for missing deducing-this in Clang 17
  std::function<void(Coord, int64_t)> try_explore = [&](Coord coord,
                                                        int64_t distance) {
    if (coord.row < 0)
      return;
    if (coord.col < 0)
      return;
    if (coord.row >= std::ssize(map))
      return;
    if (coord.col >= std::ssize(map[coord.row]))
      return;
    if (map[coord.row][coord.col] == '#')
      return;

    // Handle slopes by eagerly processing them
    if (map[coord.row][coord.col] == '>') {
      try_explore({coord.row, coord.col + 1}, distance + 1);
      return;
    }
    if (map[coord.row][coord.col] == '<') {
      try_explore({coord.row, coord.col - 1}, distance + 1);
      return;
    }
    if (map[coord.row][coord.col] == 'v') {
      try_explore({coord.row + 1, coord.col}, distance + 1);
      return;
    }
    if (map[coord.row][coord.col] == '^') {
      try_explore({coord.row - 1, coord.col}, distance + 1);
      return;
    }
    if (visited.contains(coord))
      return;
    dfs.push_back({coord, distance, 0});
    visited.insert(coord);
  };

  try_explore(start, 0);

  int64_t max = 0;
  while (not dfs.empty()) {
    auto &[coord, distance, state] = dfs.back();
    if (coord == exit) {
      max = std::max(max, distance);
      dfs.pop_back();
      visited.erase(coord);
    }
    switch (state) {
    case 0:
      ++state;
      try_explore({coord.row - 1, coord.col}, distance + 1);
      break;
    case 1:
      ++state;
      try_explore({coord.row + 1, coord.col}, distance + 1);
      break;
    case 2:
      ++state;
      try_explore({coord.row, coord.col + 1}, distance + 1);
      break;
    case 3:
      ++state;
      try_explore({coord.row, coord.col - 1}, distance + 1);
      break;
    case 4:
      dfs.pop_back();
      visited.erase(coord);
      break;
    }
  }

  return max;
}
} // namespace

export namespace part_one {
int64_t longest_scenic_route(std::span<const char> map) {
  std::vector<std::string_view> grid;
  std::ranges::transform(map | std::views::split('\n'),
                         std::back_inserter(grid),
                         [](auto &&rng) { return std::string_view(rng); });

  Coord start = {0, 1};
  Coord exit = {std::ssize(grid) - 1, std::ssize(grid[0]) - 2};
  return max_path(grid, start, exit);
}
} // namespace part_one