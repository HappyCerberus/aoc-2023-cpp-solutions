module;

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <ranges>
#include <span>
#include <spanstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

export module part_two;

export namespace part_two {
int64_t simulate(std::span<const char> map) {
  // Flatten the map into a 1D array
  std::vector<char> grid;
  std::ranges::copy(map | std::views::split('\n') | std::views::join,
                    std::back_inserter(grid));

  auto shift = [&](auto rng) {
    // First available space to the left
    auto dst = rng.begin();
    // Currently examined space
    auto src = rng.begin();
    while (true) {
      // Jump to the next empty space
      while (dst != rng.end() && *dst != '.')
        ++dst;
      // No empty spaces, we are done
      if (dst == rng.end())
        break;
      // We are shifting to the left, so our src has to be to the right of dst
      src = dst;
      // Find the next non-empty space
      while (src != rng.end() && *src == '.')
        ++src;
      // All empty spaces, we are done
      if (src == rng.end())
        break;
      // If its a 'O', shift it to dst
      if (*src == 'O') {
        std::iter_swap(src, dst);
        // If its '#' shift dst
      } else if (*src == '#') {
        dst = src;
      }
    }
  };

  int64_t row_count = std::ranges::count_if(map | std::views::split('\n'),
                                            [](auto) { return true; });
  int64_t col_count = std::ranges::count_if(
      map | std::views::split('\n') | std::views::take(1) | std::views::join,
      [](auto) { return true; });

  auto one_iteration = [&]() {
    // North
    for (int64_t col = 0; col < col_count; ++col)
      shift(grid | std::views::drop(col) | std::views::stride(col_count));

    // West
    for (auto row : grid | std::views::chunk(col_count))
      shift(row);

    // South
    for (int64_t col = 0; col < col_count; ++col)
      shift(grid | std::views::drop(col) | std::views::stride(col_count) |
            std::views::reverse);

    // East
    for (auto row : grid | std::views::chunk(col_count))
      shift(row | std::views::reverse);
  };

  std::unordered_map<std::string, int64_t> visited;
  std::vector<char> prev;
  int64_t ticks = 0;
  while (true) {
    visited.insert({std::string(grid.begin(), grid.end()), ticks});
    ++ticks;
    one_iteration();
    auto it = visited.find(std::string(grid.begin(), grid.end()));
    if (it != visited.end()) {
      // We have visited this state before
      // Iterate until a clean loop multiple
      for (int64_t remaining = (1'000'000'000 - ticks) % (ticks - it->second);
           remaining > 0; --remaining)
        one_iteration();
      break;
    }
  }

  int64_t weight = 0;
  for (auto [ridx, row] :
       grid | std::views::chunk(col_count) | std::views::enumerate)
    weight += std::ranges::count(row, 'O') * (row_count - ridx);

  return weight;
}
} // namespace part_two