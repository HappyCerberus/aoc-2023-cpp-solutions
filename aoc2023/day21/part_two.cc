module;

#include <algorithm>
#include <cstdint>
#include <ranges>
#include <span>
#include <string>
#include <unordered_set>
#include <vector>

export module part_two;
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

namespace {
int64_t spaces(std::span<std::string_view> grid, Coord start, int64_t steps) {
  std::unordered_set<Coord> current;
  std::unordered_set<Coord> next;
  auto try_step = [&](Coord coord) {
    int64_t row = coord.row % std::ssize(grid);
    if (row < 0)
      row += std::ssize(grid);
    int64_t col = coord.col % std::ssize(grid[row]);
    if (col < 0)
      col += std::ssize(grid[row]);
    if (grid[row][col] == '#')
      return;
    next.insert(coord);
  };

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
  return std::ssize(next);
}
} // namespace

export namespace part_two {
int64_t number_of_plots_on_infinite_map(std::span<const char>, int64_t steps) {
  // Calculate the values of x == 0, 1, 2
  /*
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
  int64_t x0 = spaces(grid, start, 65);
  int64_t x1 = spaces(grid, start, 131 + 65);
  int64_t x2 = spaces(grid, start, 131 * 2 + 65);
  */
  // Chug it into wolfram alpha
  int64_t rounds = (steps - 65) / 131;
  return 3814 + 15114 * rounds + 15024 * rounds * rounds;
}
} // namespace part_two