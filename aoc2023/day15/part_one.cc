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
int64_t sum_of_hashes(std::string_view sequence) {
  auto hash = [](auto step) {
    return std::ranges::fold_left(step, 0z, [](int64_t current, char c) {
      current += int64_t{c};
      current *= 17;
      return current % 256;
    });
  };
  return std::ranges::fold_left(sequence | std::views::split(',') |
                                    std::views::transform(hash),
                                0z, std::plus<>{});
}
} // namespace part_one