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

export module part_two;

namespace {
struct Note {
  std::vector<uint64_t> rows;
  std::vector<uint64_t> cols;

  friend std::istream &operator>>(std::istream &s, Note &note) {
    if (s.peek() == std::char_traits<char>::eof())
      return s;
    note.rows.clear();
    note.cols.clear();
    // Empty line signifies the end of one note
    while (s) {
      if (s.peek() == '\n') {
        s.ignore();
        return s;
      }

      // Read one row
      uint64_t number = 0;
      uint64_t column = 0;
      while (s) {
        char c = s.get();
        // Treat '.' as 0 bit
        if (c == '.') {
          number = number << 1;
          if (note.cols.size() == column)
            note.cols.push_back(0);
          else
            note.cols[column] = note.cols[column] << 1;
          // Treat '#' as 1 bit
        } else if (c == '#') {
          number = (number << 1) | 1;
          if (note.cols.size() == column)
            note.cols.push_back(1);
          else
            note.cols[column] = (note.cols[column] << 1) | 1;
        } else if (c == '\n') {
          break;
        }
        ++column;
      }
      note.rows.push_back(number);
    }
    if (s.eof())
      s.clear(std::ios::eofbit);
    return s;
  }
  static int64_t mirror(std::span<const uint64_t> rng) {
    auto all_splits =
        std::views::iota(rng.begin(), rng.end()) |
        std::views::transform([&](auto it) {
          return std::pair{std::ranges::subrange(rng.begin(), it) |
                               std::views::reverse,
                           std::ranges::subrange(it, rng.end())};
        });
    // Again, iterate over all splits
    for (auto [prefix, suffix] : all_splits) {
      // Only proper splits
      if (prefix.empty() || suffix.empty())
        continue;
      // Count the number of bit errors
      uint64_t bitcount = 0;
      // inner_product uses the first range for length information, we need to
      // make sure that the first range is the shorter one
      if (prefix.size() >= suffix.size()) {
        bitcount = std::inner_product(
            suffix.begin(), suffix.end(), prefix.begin(), 0uz, std::plus<>{},
            [](uint64_t left, uint64_t right) {
              return std::popcount(left ^ right); // number of different bits
            });
      } else {
        bitcount = std::inner_product(
            prefix.begin(), prefix.end(), suffix.begin(), 0uz, std::plus<>{},
            [](uint64_t left, uint64_t right) {
              return std::popcount(left ^ right); // number of different bits
            });
      }
      // If we have exactly one bit error, we have our mirror line
      if (bitcount == 1)
        return prefix.size();
    }
    return 0;
  }
  int64_t row_mirror() const { return mirror(rows); }
  int64_t col_mirror() const { return mirror(cols); }
};
} // namespace

export namespace part_two {
int64_t summarize_notes_with_error(std::span<const char> map) {
  std::ispanstream s(map);
  // Sum up the mirror information
  return std::ranges::fold_left(
      std::views::istream<Note>(s), 0z, [](int64_t acc, const Note &note) {
        return acc + note.col_mirror() + 100 * note.row_mirror();
      });
}
} // namespace part_two