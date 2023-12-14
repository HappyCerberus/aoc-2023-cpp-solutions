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
#include <unordered_set>
#include <vector>

export module part_one;

export namespace part_one {
int64_t total_load(std::string_view map) {
  std::vector<std::string_view> grid;
  std::ranges::transform(
      map | std::views::split('\n'), std::back_inserter(grid),
      [](auto rng) { return std::string_view(rng.begin(), rng.end()); });

  // Last seen position of '#'
  std::vector<int64_t> positions(grid[0].size(), -1);
  // Number of 'O' stacked bellow the last '#'
  std::vector<int64_t> counts(grid[0].size(), 0);

  int64_t weight = 0;
  for (int64_t row = 0; row < std::ssize(grid); ++row) {
    for (int64_t col = 0; col < std::ssize(grid[row]); ++col) {
      // Count the 'O'
      if (grid[row][col] == 'O') {
        ++counts[col];
        // When we see a '#' we need to turn the current count[col] into a
        // weight
      } else if (grid[row][col] == '#') {
        // Each stacked 'O' is one row lower than the previous one
        while (counts[col] > 0) {
          ++positions[col];
          weight += std::ssize(grid) - positions[col];
          --counts[col];
        }
        positions[col] = row;
      }
    }
  }

  // The weight of 'O's that are not capped by any '#'
  for (int64_t col = 0; col < std::ssize(counts); ++col) {
    while (counts[col] > 0) {
      ++positions[col];
      weight += std::ssize(grid) - positions[col];
      --counts[col];
    }
  }

  return weight;
}
} // namespace part_one