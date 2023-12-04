module;

#include <algorithm>
#include <cstdint>
#include <ranges>
#include <span>
#include <spanstream>
#include <vector>

export module part_two;

export namespace part_two {
int64_t total_scratchcards(std::span<const char> scratchcards) {
  struct Info {
    int64_t cnt;
    uint64_t matches;
  };

  // Same logic as in part one:
  auto line_to_matches = [](auto &&line) {
    std::array<std::vector<int64_t>, 2> scratchcards;
    for (auto &&[idx, chunk] :
         line | std::views::drop_while([](char c) { return c != ':'; }) |
             std::views::drop(1) | std::views::split('|') |
             std::views::enumerate) {
      std::ispanstream s(chunk);
      std::ranges::copy(std::views::istream<int64_t>(s),
                        std::back_inserter(scratchcards[idx]));
    }
    std::ranges::sort(scratchcards[0]);
    std::ranges::sort(scratchcards[1]);
    std::vector<int64_t> out;
    std::ranges::set_intersection(scratchcards[0], scratchcards[1],
                                  std::back_inserter(out));
    // Instead of returning score, return a pair of 1
    // (since we start with one copy of each card)
    // and the number of matching numbers
    return Info{1z, out.size()};
  };

  // Fill the vector with information about the matches for each card, with the
  // count initialized to 1.
  std::vector<Info> cards;
  std::ranges::copy(scratchcards | std::views::split('\n') |
                        std::views::transform(line_to_matches),
                    std::back_inserter(cards));

  // Now process all the cards, for each card, add the number of copies of this
  // card to the "number of matches" number of cards after this one
  for (size_t i = 0; i < cards.size(); ++i)
    for (size_t j = i + 1; j <= i + cards[i].matches; ++j)
      cards[j].cnt += cards[i].cnt;

  // At this point we have the total count of each card for each card all we
  // have to do is to sum it all up.
  return std::ranges::fold_left(cards | std::views::transform(&Info::cnt), 0z,
                                std::plus<>{});
}
} // namespace part_two