module;

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <list>
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

namespace {
int64_t hash(std::string_view label) {
  return std::ranges::fold_left(label, 0z, [](int64_t current, char c) {
    current += int64_t{c};
    current *= 17;
    return current % 256;
  });
}

struct HashMap {
  HashMap() : store_(256) {}

  void pop(std::string_view label) {
    store_[hash(label)].remove_if(
        [&](const auto &pair) { return pair.first == label; });
  }

  void push(std::string_view label, int64_t value) {
    int64_t key = hash(label);
    auto it = std::ranges::find_if(
        store_[key], [&](const auto &pair) { return pair.first == label; });
    // If the key already exits, update
    if (it != store_[key].end())
      it->second = value;
    else
      // Otherwise insert
      store_[key].push_back(std::pair{std::string{label}, value});
  }

  int64_t value() const {
    int64_t sum = 0;
    for (const auto &[bucket, list] : store_ | std::views::enumerate)
      for (const auto &[slot, value] : list | std::views::enumerate)
        sum += (bucket + 1) * (slot + 1) * value.second;
    return sum;
  }

private:
  std::vector<std::list<std::pair<std::string, int64_t>>> store_;
};
} // namespace

export namespace part_two {
int64_t hashmap_value(std::string_view instructions) {
  HashMap hashmap;
  for (const auto &instruction : instructions | std::views::split(',')) {
    // Find the delimiter
    auto it = std::ranges::find_if(instruction,
                                   [](char c) { return c == '=' || c == '-'; });
    if (it == instruction.end())
      throw std::runtime_error("malformed instruction");

    if (*it == '=') {
      auto label =
          std::string_view(instruction).substr(0, it - instruction.begin());
      // We are working non-null-terminated strings, from_chars is designed for
      // this use case
      int64_t value;
      if (auto [ptr, err] =
              std::from_chars(std::next(it), instruction.end(), value);
          err != std::errc{})
        throw std::runtime_error("parsing error, couldn't parse lense size");

      hashmap.push(label, value);
    } else if (*it == '-') {
      auto label =
          std::string_view(instruction).substr(0, it - instruction.begin());

      hashmap.pop(label);
    }
  }
  return hashmap.value();
}
} // namespace part_two