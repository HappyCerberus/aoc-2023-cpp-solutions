module;

#include <algorithm>
#include <functional>
#include <iostream>
#include <ranges>
#include <span>
#include <spanstream>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <vector>

export module part_two;

namespace {
struct Spring {
  std::string condition;
  std::vector<int64_t> numeric;
  friend std::istream &operator>>(std::istream &s, Spring &spring) {
    std::string condition;
    if (not(s >> condition))
      return s;
    std::vector<int64_t> numeric;
    int64_t number = 0;
    do {
      if (s.peek() == ',')
        s.ignore();
      if (not(s >> number))
        return s;
      numeric.push_back(number);
    } while (s.peek() == ',');
    spring.condition = condition;
    for (int i = 0; i < 4; ++i) {
      spring.condition += '?';
      spring.condition += condition;
    }
    spring.numeric = numeric;
    for (int i = 0; i < 4; ++i) {
      std::ranges::copy(numeric, std::back_inserter(spring.numeric));
    }
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

int64_t count(auto &cache_, int64_t offset, std::span<const int64_t> cant_skip,
              std::span<const int64_t> values,
              std::span<const std::vector<int64_t>> positions) {
  // Check the cache
  auto cache_it = cache_.find(offset);
  if (cache_it != cache_.end()) {
    auto value_it = cache_it->second.find(values.size());
    if (value_it != cache_it->second.end())
      return value_it->second;
  }

  // No more springs to place, check if we have any uncovered '#' at the end
  if (positions.size() == 0) {
    if (std::ranges::lower_bound(cant_skip, offset) == cant_skip.end()) {
      cache_[offset][values.size()] = 1;
      return 1;
    } else {
      cache_[offset][values.size()] = 0;
      return 0;
    }
  }

  // Find the earliest position we can use
  auto lower = std::ranges::lower_bound(positions[0], offset);
  if (lower == positions[0].end()) { // No feasible positions
    cache_[offset][values.size()] = 0;
    return 0;
  }

  // Find the earliest '#' that still needs to be covered
  auto upper = std::ranges::lower_bound(cant_skip, offset);

  int64_t sum = 0;
  for (auto pos : std::ranges::subrange(lower, positions[0].end())) {
    // We cannot skip over the '#'
    if (upper != cant_skip.end() && pos > *upper)
      break;
    // Use this position and recurse to calculate the combinations for the
    // suffix / remainder of springs
    sum += count(cache_, pos + values[0] + 1, cant_skip, values.subspan(1),
                 positions.subspan(1));
  }
  cache_[offset][values.size()] = sum;
  return sum;
}

int64_t count(const Spring &spring) {
  // The cache is per-line
  std::unordered_map<int64_t, std::unordered_map<size_t, int64_t>> cache_;
  // Generate all placements
  auto positions = all_placements(spring.condition, spring.numeric);
  // Extract positions of '#' in the text representation
  std::vector<int64_t> cant_skip;
  for (auto [idx, c] : spring.condition | std::views::enumerate)
    if (c == '#')
      cant_skip.push_back(idx);
  return count(cache_, 0, cant_skip, spring.numeric, positions);
}

// The last spring needs to check for leftover uncovered '#' on the right
std::vector<std::pair<int64_t, int64_t>>
count_last(int64_t value, std::span<const int64_t> positions,
           std::span<const int64_t> cant_skip) {
  std::vector<std::pair<int64_t, int64_t>> result;
  for (auto pos : positions) {
    // The position is only valid if it doesn't leave any uncovered '#' on the
    // right
    auto lb = std::ranges::lower_bound(cant_skip, pos + value + 1);
    if (lb == cant_skip.end())
      result.push_back({pos, 1});
    else
      result.push_back({pos, 0});
  }
  return result;
}

// Replacement count function that takes the results from the previous iteration
std::vector<std::pair<int64_t, int64_t>>
count_next(std::span<const std::pair<int64_t, int64_t>> prev, int64_t value,
           std::span<const int64_t> positions,
           std::span<const int64_t> cant_skip) {
  std::vector<std::pair<int64_t, int64_t>> result;
  for (auto pos : positions) {
    auto lower = std::ranges::lower_bound(prev, pos + value + 1, std::less<>{},
                                          &std::pair<int64_t, int64_t>::first);
    result.push_back(
        {pos, std::ranges::fold_left(
                  std::ranges::subrange(lower, prev.end()), 0z,
                  [&](int64_t acc, std::pair<int64_t, int64_t> prev_info) {
                    // Check that we are not leaving any '#' in between
                    auto skip_lower =
                        std::ranges::lower_bound(cant_skip, pos + value + 1);
                    auto skip_upper =
                        std::ranges::lower_bound(cant_skip, prev_info.first);
                    if (skip_lower != skip_upper)
                      return acc;
                    return acc + prev_info.second;
                  })});
  }
  return result;
}

int64_t count_new(const Spring &spring) {
  // Generate all placements
  auto positions = all_placements(spring.condition, spring.numeric);
  // Extract positions of '#' in the text representation
  std::vector<int64_t> cant_skip;
  for (auto [idx, c] : spring.condition | std::views::enumerate)
    if (c == '#')
      cant_skip.push_back(idx);
  // Counts for the last element in the numeric representation
  auto last = count_last(spring.numeric.back(), positions.back(), cant_skip);
  // Iterate in reverse
  for (int64_t idx = std::size(spring.numeric) - 2; idx >= 0; --idx) {
    auto curr =
        count_next(last, spring.numeric[idx], positions[idx], cant_skip);
    last = std::move(curr);
  }
  // As we compute we check that we are not skipping trailing '#', we still need
  // to check if there any uncovered '#' on the left
  auto end = last.end();
  if (not cant_skip.empty())
    end = std::ranges::upper_bound(last, cant_skip[0], std::less<>{},
                                   &std::pair<int64_t, int64_t>::first);
  // Sum up the computed possibilites for the first spring
  return std::ranges::fold_left(
      std::ranges::subrange(last.begin(), end), 0z,
      [](int64_t acc, std::pair<int64_t, int64_t> &e) {
        return acc + e.second;
      });
}
} // namespace

export namespace part_two {
int64_t sum_of_long_options(std::span<const char> springs) {
  std::ispanstream s(springs);
  return std::ranges::fold_left(std::views::istream<Spring>(s), 0z,
                                [](int64_t acc, const Spring &spring) {
                                  if (count_new(spring) != count(spring))
                                    throw "Mismatch";
                                  return acc + count(spring);
                                });
}
} // namespace part_two