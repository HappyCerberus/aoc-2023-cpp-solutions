module;

#include <algorithm>
#include <cstdint>
#include <ranges>
#include <string_view>
#include <unordered_map>
#include <vector>

export module part_two;

namespace {
struct Number {
  int64_t value;
  int64_t col_begin;
  int64_t col_end;
  bool operator<(const Number &other) const {
    return col_begin < other.col_begin;
  }
};
struct NumberStore {
  std::span<Number> get_next_to(int64_t col) {
    // Find the first number whose column start is not less than col.
    auto first =
        std::ranges::lower_bound(numbers, Number{0, col, 0}, std::less<>{});
    auto last = first;
    // [first,last) starts as an empty range, because first == last.

    // We want to include last if its column is col or col+1 (we already know it
    // is not less than col)
    if (last != numbers.end())
      if (last->col_begin == col || last->col_begin == col + 1)
        std::advance(last, 1);
    // We want to include the previous number if its end is at least col - 1
    if (first != numbers.begin())
      if (std::prev(first)->col_end >= col - 1)
        std::advance(first, -1);

    return std::ranges::subrange(first, last);
  }
  std::vector<Number> numbers;
};
} // namespace

export namespace part_two {
int64_t gear_ratios(std::string_view schematic) {
  std::unordered_map<int64_t, NumberStore> store;
  std::vector<std::pair<int64_t, int64_t>> gears;
  for (auto [row, line] :
       schematic | std::views::split('\n') | std::views::enumerate) {

    // Current number
    std::optional<int64_t> number;
    // The starting column for the current number
    std::optional<int64_t> col_start;

    for (int64_t col = 0; col < std::ssize(line); ++col) {
      // Remember gears
      if (line[col] == '*')
        gears.emplace_back(row, col);

      // Parse numbers
      if (std::isdigit(line[col])) {
        if (number) {
          *number *= 10;
          *number += line[col] - '0';
        } else {
          number = line[col] - '0';
          col_start = col;
        }
      } else if (number) {
        // Current character is not a digit and we have a number
        store[row].numbers.emplace_back(*number, *col_start, col - 1);

        // Reset
        number = {};
        col_start = {};
      }
    }
    // And as before, a number can be terminated by end of line
    if (number) {
      store[row].numbers.emplace_back(*number, *col_start,
                                      std::ssize(line) - 1);
    }
  }

  auto get_ratio = [&](std::pair<int64_t, int64_t> coord) {
    // Adjacent numbers on the three surounding rows
    auto numbers = {store[coord.first - 1].get_next_to(coord.second),
                    store[coord.first].get_next_to(coord.second),
                    store[coord.first + 1].get_next_to(coord.second)};
    // Each one is a range of 0..2 numbers, with join we treat them as a single
    // range.
    auto joined = numbers | std::views::join;
    // Check if this is a proper gear.
    if (std::ranges::count_if(joined, [](auto &) { return true; }) != 2)
      return 0z;
    // If it is, return the product.
    return std::ranges::fold_left(joined |
                                      std::views::transform(&Number::value),
                                  1z, std::multiplies<>{});
  };

  return std::ranges::fold_left(gears | std::views::transform(get_ratio), 0z,
                                std::plus<>{});
}
} // namespace part_two