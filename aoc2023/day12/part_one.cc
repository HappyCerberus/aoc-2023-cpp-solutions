module;

#include <algorithm>
#include <iostream>
#include <ranges>
#include <span>
#include <spanstream>
#include <string_view>
#include <unordered_set>
#include <vector>

export module part_one;

namespace {
struct Spring {
  std::string condition;
  std::vector<int64_t> numeric;

  friend std::istream &operator>>(std::istream &s, Spring &spring) {
    if (not(s >> spring.condition))
      return s;
    spring.numeric.clear();
    int64_t number = 0;
    do {
      if (s.peek() == ',')
        s.ignore();
      if (not(s >> number))
        return s;
      spring.numeric.push_back(number);
    } while (s.peek() == ',');
    if (s.eof()) {
      s.clear(std::ios::eofbit);
    }
    return s;
  }
};

std::vector<int64_t> possible_placements(int64_t offset, int64_t width,
                                         std::string_view condition) {
  std::vector<int64_t> result;
  int64_t i = offset;
  int64_t j = i;
  // Scan for possible placements using a two-pointer technique
  while (i < std::ssize(condition)) {
    // Find the next feasible start
    while (condition[i] == '.' && i < std::ssize(condition)) {
      ++i;
      ++j;
    }
    // Find the end after the start
    if (i == std::ssize(condition))
      break;
    while (condition[j] != '.' && j < std::ssize(condition)) {
      ++j;
    }
    // For all possible placements of the width within the window
    for (int k = i; k <= j - width; ++k) {
      // Ensure that the placement is bounded by '.' or '?' characters, not '#'
      if ((k - 1 == -1 || condition[k - 1] != '#') &&
          (k + width == std::ssize(condition) || condition[k + width] != '#'))
        result.push_back(k);
    }
    i = j;
  }
  return result;
}

std::vector<std::vector<int64_t>>
all_placements(std::string_view condition, std::span<const int64_t> numeric) {
  std::vector<std::vector<int64_t>> result;
  std::string_view suffix = condition;
  int64_t offset = 0;
  // Generate the possible placement for all values in the right-side encoding
  // while keeping track of the earliest possible start.
  for (auto v : numeric) {
    result.push_back(possible_placements(offset, v, suffix));
    if (result.back().size() == 0) {
      offset = std::ssize(suffix);
    } else {
      offset = result.back()[0] + v + 1;
    }
  }
  return result;
}

int64_t count(int64_t offset, std::span<const int64_t> cant_skip,
              std::span<const int64_t> values,
              std::span<const std::vector<int64_t>> positions) {
  // No more springs to place, check if we have any uncovered '#' at the end
  if (positions.size() == 0) {
    if (std::ranges::lower_bound(cant_skip, offset) == cant_skip.end())
      return 1;
    else
      return 0;
  }

  // Find the earliest position we can use
  auto lower = std::ranges::lower_bound(positions[0], offset);
  if (lower == positions[0].end()) // No feasible positions
    return 0;

  // Find the earliest '#' that still needs to be covered
  auto upper = std::ranges::lower_bound(cant_skip, offset);

  int64_t sum = 0;
  for (auto pos : std::ranges::subrange(lower, positions[0].end())) {
    // We cannot skip over the '#'
    if (upper != cant_skip.end() && pos > *upper)
      break;
    // Use this position and recurse to calculate the combinations for the
    // suffix / remainder of springs
    sum += count(pos + values[0] + 1, cant_skip, values.subspan(1),
                 positions.subspan(1));
  }
  return sum;
}

int64_t count(const Spring &spring) {
  // Generate all placements
  auto positions = all_placements(spring.condition, spring.numeric);
  // Extract positions of '#' in the text representation
  std::vector<int64_t> cant_skip;
  for (auto [idx, c] : spring.condition | std::views::enumerate)
    if (c == '#')
      cant_skip.push_back(idx);
  return count(0, cant_skip, spring.numeric, positions);
}
} // namespace

export namespace part_one {
int64_t sum_of_options(std::span<const char> springs) {
  std::ispanstream s(springs);
  return std::ranges::fold_left(
      std::views::istream<Spring>(s), 0z,
      [](int64_t acc, const Spring &spring) { return acc + count(spring); });
}
} // namespace part_one