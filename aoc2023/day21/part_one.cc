module;

#include <algorithm>
#include <cstdint>
#include <ranges>
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
    std::size_t h2 = std::hash<int64_t>{}(c.row);
    return h1 ^ (h2 << 1);
  }
};

export namespace part_one {
int64_t number_of_plots(std::span<const char> map, int64_t steps) {
  std::vector<std::string_view> grid;
  std::ranges::transform(map | std::views::split('\n'),
                         std::back_inserter(grid),
                         [](auto &&rng) { return std::string_view(rng); });

  Coord start = [&] {
    for (int64_t row = 0; row < std::ssize(grid); ++row)
      for (int64_t col = 0; col < std::ssize(grid[row]); ++col)
        if (grid[row][col] == 'S')
          return Coord{row, col};
    return Coord{};
  }();

  std::unordered_set<Coord> current;
  std::unordered_set<Coord> next;
  // Helper that checks for boundaries and walls
  auto try_step = [&](Coord coord) {
    if (coord.row < 0)
      return;
    if (coord.col < 0)
      return;
    if (coord.row >= std::ssize(grid))
      return;
    if (coord.col >= std::ssize(grid[coord.row]))
      return;
    if (grid[coord.row][coord.col] == '#')
      return;
    next.insert(coord);
  };

  // Loop. Expand all visited spaces, then flip to the next set.
  // Repeat "steps" times.
  try_step(start);
  std::ranges::for_each(std::views::iota(0, steps), [&](auto) {
    current = next;
    next.clear();
    for (auto coord : current) {
      try_step({coord.row - 1, coord.col});
      try_step({coord.row + 1, coord.col});
      try_step({coord.row, coord.col - 1});
      try_step({coord.row, coord.col + 1});
    }
  });
  return next.size();
}
} // namespace part_one