module;

#include <algorithm>
#include <ranges>
#include <span>
#include <spanstream>
#include <vector>

export module part_one;

import formula;

export namespace part_one {
int64_t product_of_number_of_solutions(std::span<const char> document) {
  std::vector<int64_t> times;
  std::vector<int64_t> distances;

  // Parse the input
  std::ispanstream s(document);
  auto skip_text = [&] {
    while (not std::isdigit(s.peek()))
      s.ignore();
  };

  skip_text();
  std::ranges::copy(std::views::istream<int64_t>(s), std::back_inserter(times));
  s.clear();
  skip_text();
  std::ranges::copy(std::views::istream<int64_t>(s),
                    std::back_inserter(distances));

  return std::ranges::fold_left(
      std::views::zip(times, distances), 1z, [&](int64_t acc, const auto &e) {
        return acc * formula::count_solutions(e.first, e.second);
      });
}
} // namespace part_one