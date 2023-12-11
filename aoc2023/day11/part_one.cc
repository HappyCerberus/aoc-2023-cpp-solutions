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
};
} // namespace

export namespace part_one {
int64_t sum_of_distances(std::string_view map) {
  // Helper that checks whether all characters in a range all spaces
  auto all_space = [](const auto &e) {
    return std::ranges::all_of(std::get<1>(e), [](char c) { return c == '.'; });
  };
  // Helper that extracts the index from a tupple
  auto to_index = [](const auto &e) { return std::get<0>(e); };

  std::vector<int64_t> empty_rows;
  // Get indexes of empty lines:
  // split by line, attach an index to each line, filter lines that are only
  // empty spaces, keep only the index
  std::ranges::copy(map | std::views::split('\n') | std::views::enumerate |
                        std::views::filter(all_space) |
                        std::views::transform(to_index),
                    std::back_inserter(empty_rows));

  std::vector<int64_t> empty_columns;
  int64_t line_length =
      std::ranges::count_if(map | std::views::split('\n') |
                                std::views::take(1) | std::views::join,
                            [](char) { return true; }) +
      1;
  // Get indexes of empty columns:
  // produce column views (views over each nth element, incrementally offset),
  // attach an index to each view, filter for views that only contain empty
  // spaces, keep the index only
  std::ranges::copy(std::views::iota(0, line_length) |
                        std::views::transform([&](int64_t off) {
                          return map | std::views::drop(off) |
                                 std::views::stride(line_length);
                        }) |
                        std::views::enumerate | std::views::filter(all_space) |
                        std::views::transform(to_index),
                    std::back_inserter(empty_columns));

  // Distance calculation helper
  // determine the number of empty rows and columns between the two coordinates
  // then calculate the distance, adding the appropriate weight to the empty
  // rows/columns
  auto distance = [&](Coord first, Coord second) {
    int64_t columns = std::ranges::distance(
        std::ranges::upper_bound(empty_columns,
                                 std::min(first.col, second.col)),
        std::ranges::lower_bound(empty_columns,
                                 std::max(first.col, second.col)));
    int64_t rows = std::ranges::distance(
        std::ranges::upper_bound(empty_rows, std::min(first.row, second.row)),
        std::ranges::lower_bound(empty_rows, std::max(first.row, second.row)));
    return std::abs(first.col - second.col) + columns +
           std::abs(first.row - second.row) + rows;
  };

  std::vector<Coord> seen;
  // Transform the map into the list of coordinates of galaxies
  // then fold over the galaxies, for each producing the sum of distances to all
  // previously seen galaxies.
  auto all_galaxies = map | std::views::split('\n') | std::views::enumerate |
                      std::views::transform([](auto &&e) {
                        auto &&[idx, line] = e;
                        return line | std::views::enumerate |
                               std::views::filter([](auto &&f) {
                                 auto &&[cidx, c] = f;
                                 return c == '#';
                               }) |
                               std::views::transform([idx](auto &&f) {
                                 auto &&[cidx, c] = f;
                                 return Coord{idx, cidx};
                               });
                      }) |
                      std::views::join;
  return std::ranges::fold_left(all_galaxies, 0z, [&](int64_t acc, Coord c) {
    int64_t result = acc + std::ranges::fold_left(
                               seen, 0z, [&](int64_t inner_acc, Coord inner_c) {
                                 return inner_acc + distance(c, inner_c);
                               });
    seen.push_back(c);
    return result;
  });
}
} // namespace part_one