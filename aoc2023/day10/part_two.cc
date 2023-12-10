module;

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <ranges>
#include <span>
#include <spanstream>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <vector>

export module part_two;

namespace {
struct Coord {
  int64_t row;
  int64_t col;
  auto operator<=>(const Coord &) const = default;
  Coord operator+(const Coord &other) {
    return Coord{row + other.row, col + other.col};
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
int64_t encircled_spaces(std::string_view map) {
  // Turn the input into a 2d grid
  std::vector<std::string_view> grid;
  std::ranges::copy(map | std::views::split('\n') |
                        std::views::transform([](auto &&rng) {
                          return std::string_view(rng.begin(), rng.end());
                        }),
                    std::back_inserter(grid));

  Coord start = [&] {
    for (int64_t r = 0; r < std::ssize(grid); ++r)
      for (int64_t c = 0; c < std::ssize(grid[r]); ++c)
        if (grid[r][c] == 'S')
          return Coord{r, c};
    return Coord{0, 0};
  }();

  std::unordered_map<char, std::pair<Coord, Coord>> offsets{
      {'|', {{-1, 0}, {+1, 0}}}, // North/South
      {'-', {{0, -1}, {0, +1}}}, // West/East
      {'L', {{-1, 0}, {0, +1}}}, // North/East
      {'J', {{-1, 0}, {0, -1}}}, // North/West
      {'7', {{+1, 0}, {0, -1}}}, // South/West
      {'F', {{+1, 0}, {0, +1}}}  // South/East
  };
  std::unordered_map<Coord, int64_t> visited;

  std::queue<std::pair<Coord, int64_t>> q;
  q.push({start, 0});
  visited[start] = 0;

  auto can_step = [&](Coord from, Coord c) {
    if (c.row < 0 || c.col < 0)
      return false;
    if (c.row >= std::ssize(grid))
      return false;
    if (c.col >= std::ssize(grid[c.row]))
      return false;
    // Does the destination pipe connect to the source
    auto [a, b] = offsets[grid[c.row][c.col]];
    if (from != c + a && from != c + b)
      return false;
    return true;
  };

  auto try_visit = [&](Coord from, Coord c, int64_t distance) {
    if (not can_step(from, c))
      return false;
    auto it = visited.find(c);
    if (it != visited.end()) {
      if (it->second != distance)
        return false;
      return true;
    }
    q.push({c, distance});
    visited[c] = distance;
    return false;
  };

  // Decode the proper type for the start space
  char start_space = [&] {
    if (can_step(start, {start.row - 1, start.col}) &&
        can_step(start, {start.row + 1, start.col}))
      return '|';
    if (can_step(start, {start.row, start.col - 1}) &&
        can_step(start, {start.row, start.col + 1}))
      return '-';
    if (can_step(start, {start.row - 1, start.col}) &&
        can_step(start, {start.row, start.col + 1}))
      return 'L';
    if (can_step(start, {start.row - 1, start.col}) &&
        can_step(start, {start.row, start.col - 1}))
      return 'J';
    if (can_step(start, {start.row + 1, start.col}) &&
        can_step(start, {start.row, start.col + 1}))
      return 'F';
    if (can_step(start, {start.row + 1, start.col}) &&
        can_step(start, {start.row, start.col - 1}))
      return '7';
    return '.';
  }();

  // Helper that handles the start space special case
  auto getspace = [&](Coord c) {
    char space = grid[c.row][c.col];
    if (space == 'S')
      return start_space;
    return space;
  };

  while (not q.empty()) {
    auto [coord, distance] = q.front();
    q.pop();
    // Handle the start space implicitly by returning the underlying shape.
    char space = getspace(coord);
    if (space == '.')
      continue;
    auto [a, b] = offsets[space];
    if (try_visit(coord, coord + a, distance + 1) ||
        try_visit(coord, coord + b, distance + 1))
      break;
  }

  std::unordered_set<Coord> expanded_visited;
  // Similar to can_step, but in translated coordinates
  auto expanded_can_step = [&](Coord c) {
    // Out of bounds check
    if (c.row < 0 || c.col < 0)
      return false;
    if (c.row > std::ssize(grid) * 2)
      return false;
    if (c.col > std::ssize(grid[0]) * 2)
      return false;

    // Any coordinate that we already visited
    if (expanded_visited.contains(c))
      return false;

    // Odd coordinates are the original grid, we don't want to step on spaces
    // that are part of the loop.
    if (c.row % 2 != 0 && c.col % 2 != 0)
      if (visited.contains(Coord{(c.row - 1) / 2, (c.col - 1) / 2}))
        return false;

    // Otherwise we can step anywhere, except on spaces that are crossing the
    // loop.

    // Vertical case
    if (c.row % 2 == 0 && c.col % 2 != 0 && c.row != 0 &&
        c.row != std::ssize(grid) * 2) {
      // The two adjacent coordinates
      auto north = Coord{(c.row - 2) / 2, (c.col - 1) / 2};
      auto south = Coord{(c.row) / 2, (c.col - 1) / 2};
      // Are they both on the loop?
      if (not(visited.contains(north) && visited.contains(south)))
        return true;
      // If yes, do they connect through this space?
      if ((north == south + offsets[getspace(south)].first ||
           north == south + offsets[getspace(south)].second) &&
          (south == north + offsets[getspace(north)].first ||
           south == north + offsets[getspace(north)].second))
        return false;
    }

    // Horizontal case
    if (c.row % 2 != 0 && c.col % 2 == 0 && c.col != 0 &&
        c.col != std::ssize(grid) * 2) {
      // The two adjacent coordinates
      auto west = Coord{(c.row - 1) / 2, (c.col - 2) / 2};
      auto east = Coord{(c.row - 1) / 2, (c.col) / 2};
      // Are they both on the loop?
      if (not(visited.contains(west) && visited.contains(east)))
        return true;
      // If yes, do they connect through this space?
      if ((west == east + offsets[getspace(east)].first ||
           west == east + offsets[getspace(east)].second) &&
          (east == west + offsets[getspace(west)].first ||
           east == west + offsets[getspace(west)].second))
        return false;
    }

    return true;
  };

  std::queue<Coord> expanded_q;
  expanded_q.push({0, 0});
  expanded_visited.insert({0, 0});

  while (not expanded_q.empty()) {
    auto coord = expanded_q.front();
    expanded_q.pop();

    // Explore all four directions
    if (expanded_can_step({coord.row - 1, coord.col})) {
      expanded_visited.insert({coord.row - 1, coord.col});
      expanded_q.push({coord.row - 1, coord.col});
    }
    if (expanded_can_step({coord.row + 1, coord.col})) {
      expanded_visited.insert({coord.row + 1, coord.col});
      expanded_q.push({coord.row + 1, coord.col});
    }
    if (expanded_can_step({coord.row, coord.col - 1})) {
      expanded_visited.insert({coord.row, coord.col - 1});
      expanded_q.push({coord.row, coord.col - 1});
    }
    if (expanded_can_step({coord.row, coord.col + 1})) {
      expanded_visited.insert({coord.row, coord.col + 1});
      expanded_q.push({coord.row, coord.col + 1});
    }
  }

  int64_t encircled = std::ssize(grid) * std::ssize(grid[0]);
  encircled -= std::ranges::count_if(expanded_visited, [](auto &c) {
    return c.row % 2 != 0 && c.col % 2 != 0;
  });
  encircled -= std::ssize(visited);

  return encircled;
}
} // namespace part_two