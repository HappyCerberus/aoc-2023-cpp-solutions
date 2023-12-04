module;

#include <algorithm>
#include <iostream>
#include <ranges>
#include <span>
#include <spanstream>
#include <string_view>
#include <vector>

export module part_one;

export namespace part_one {
int64_t total_score(std::span<const char> scratchcards) {
  auto line_to_score = [](auto &&line) {
    // Each line has two lists of numbers
    std::array<std::vector<int64_t>, 2> cards;

    // Skip over the game prefix, then split using '|' and add an index.
    for (auto &&[idx, chunk] :
         line | std::views::drop_while([](char c) { return c != ':'; }) |
             std::views::drop(1) | std::views::split('|') |
             std::views::enumerate) {
      // Parse the part of the line and store in cards
      std::ispanstream s(chunk);
      std::ranges::copy(std::views::istream<int64_t>(s),
                        std::back_inserter(cards[idx]));
    }

    // Sort both parts and calculate intersection
    // This is O(n*logn + m*logm + (n+m))
    std::ranges::sort(cards[0]);
    std::ranges::sort(cards[1]);
    std::vector<int64_t> out;
    std::ranges::set_intersection(cards[0], cards[1], std::back_inserter(out));
    // Return the score
    return (1uz << out.size()) >> 1;
  };

  // Process each line and accumulate the score.
  return std::ranges::fold_left(scratchcards | std::views::split('\n') |
                                    std::views::transform(line_to_score),
                                0uz, std::plus<>{});
}
} // namespace part_one