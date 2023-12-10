module;

#include <algorithm>
#include <functional>
#include <queue>
#include <ranges>
#include <span>
#include <spanstream>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <vector>

export module part_one;

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

export namespace part_one {
int64_t number_of_steps(std::string_view map) {
  // Turn the input into a 2d grid
  std::vector<std::string_view> grid;
  std::ranges::copy(map | std::views::split('\n') |
                        std::views::transform([](auto &&rng) {
                          return std::string_view(rng.begin(), rng.end());
                        }),
                    std::back_inserter(grid));

  // Extract the position of the start space
  Coord start = [&] {
    for (int64_t r = 0; r < std::ssize(grid); ++r)
      for (int64_t c = 0; c < std::ssize(grid[r]); ++c)
        if (grid[r][c] == 'S')
          return Coord{r, c};
    return Coord{0, 0};
  }();

  // The shape->offsets mapping
  std::unordered_map<char, std::pair<Coord, Coord>> offsets{
      {'|', {{-1, 0}, {+1, 0}}}, // North/South
      {'-', {{0, -1}, {0, +1}}}, // West/East
      {'L', {{-1, 0}, {0, +1}}}, // North/East
      {'J', {{-1, 0}, {0, -1}}}, // North/West
      {'7', {{+1, 0}, {0, -1}}}, // South/West
      {'F', {{+1, 0}, {0, +1}}}  // South/East
  };

  // BFS, keep track of visited spaces
  // (and at which distance we visited them)
  std::unordered_map<Coord, int64_t> visited;
  std::queue<std::pair<Coord, int64_t>> q;
  q.push({start, 0});
  visited[start] = 0;

  // Helper that checks whether we can go
  // from one coordinate to another
  auto can_step = [&](Coord from, Coord c) {
    // Out of bounds checks
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

  // Helper that will return true if we have reached the destination
  // space otherwise will check if the coordinate can be visited
  // and if yes inserts into our queue.
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

  while (not q.empty()) {
    auto [coord, distance] = q.front();
    q.pop();

    // Simple handling for the start space.
    // Expand into each direction.
    // Only two of the directions will suceed.
    if (grid[coord.row][coord.col] == 'S') {
      try_visit(coord, {coord.row + 1, coord.col}, distance + 1);
      try_visit(coord, {coord.row - 1, coord.col}, distance + 1);
      try_visit(coord, {coord.row, coord.col + 1}, distance + 1);
      try_visit(coord, {coord.row, coord.col - 1}, distance + 1);
      continue;
    }
    // Nothing to do on empty spaces.
    // However we should also never step on an empty space.
    if (grid[coord.row][coord.col] == '.')
      continue;
    // Try to visit the two directions the current shape connects to.
    auto [a, b] = offsets[grid[coord.row][coord.col]];
    if (try_visit(coord, coord + a, distance + 1) ||
        try_visit(coord, coord + b, distance + 1))
      // If we get true from one of the directions, we know that
      // distance+1 is our result.
      return distance + 1;
  }
  return 0;
}
} // namespace part_one