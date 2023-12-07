module;

#include <algorithm>
#include <ranges>
#include <span>
#include <spanstream>
#include <utility>
#include <vector>

export module part_one;

namespace {
struct Card {
  enum Type {
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
  } value;

  // Make it comparable
  auto operator<=>(const Card &other) const = default;

  friend std::istream &operator>>(std::istream &s, Card &card) {
    while (std::isspace(s.peek()))
      s.ignore();
    switch (s.get()) {
    case '2':
      card.value = Two;
      break;
    case '3':
      card.value = Three;
      break;
    case '4':
      card.value = Four;
      break;
    case '5':
      card.value = Five;
      break;
    case '6':
      card.value = Six;
      break;
    case '7':
      card.value = Seven;
      break;
    case '8':
      card.value = Eight;
      break;
    case '9':
      card.value = Nine;
      break;
    case 'T':
      card.value = Ten;
      break;
    case 'J':
      card.value = Jack;
      break;
    case 'Q':
      card.value = Queen;
      break;
    case 'K':
      card.value = King;
      break;
    case 'A':
      card.value = Ace;
      break;
    default:
      s.setstate(std::ios_base::failbit);
      return s;
    }
    return s;
  }
};

struct Hand {
  std::array<Card, 5> cards;
  int64_t bid;
  enum Type {
    HighCard,
    OnePair,
    TwoPair,
    ThreeOfKind,
    FullHouse,
    FourOfKind,
    FiveOfKind
  } value;

  void analyze_hand() {
    std::array<Card, 5> sorted_cards = cards;
    std::ranges::sort(sorted_cards, std::greater<>{});

    // Translate cards into frequencies of equal cards
    std::array<int64_t, 5> freq = {1, 0, 0, 0, 0};
    auto it = freq.begin();
    for (int i = 1; i < 5; ++i) {
      if (sorted_cards[i - 1] != sorted_cards[i])
        ++it;
      ++*it;
    }
    std::ranges::sort(freq, std::greater<>{});
    // Map the frequencies to the hand type
    if (freq[0] == 5)
      value = FiveOfKind;
    else if (freq[0] == 4)
      value = FourOfKind;
    else if (freq[0] == 3 && freq[1] == 2)
      value = FullHouse;
    else if (freq[0] == 3 && freq[1] != 2)
      value = ThreeOfKind;
    else if (freq[0] == 2 && freq[1] == 2)
      value = TwoPair;
    else if (freq[0] == 2 && freq[1] != 2)
      value = OnePair;
    else
      value = HighCard;
  }

  friend std::istream &operator>>(std::istream &s, Hand &hand) {
    for (auto &e : hand.cards)
      if (not(s >> e))
        return s;
    if (not(s >> hand.bid))
      return s;
    hand.analyze_hand();
    return s;
  }

  auto operator<=>(const Hand &other) const {
    // First compare by the hand value
    auto cmp = value <=> other.value;
    if (std::is_neq(cmp))
      return cmp;
    // If the hands are the same, lexicographically compare the cards
    return cards <=> other.cards;
  }
};
} // namespace

export namespace part_one {
int64_t total_winnings(std::span<const char> hands) {
  std::ispanstream s(hands);
  std::vector<Hand> parsed_hands;
  std::ranges::copy(std::views::istream<Hand>(s),
                    std::back_inserter(parsed_hands));
  std::ranges::sort(parsed_hands, std::less<>{});
  return std::ranges::fold_left(parsed_hands | std::views::enumerate, 0z,
                                [](int64_t acc, const auto &e) {
                                  auto &[idx, hand] = e;
                                  return acc + hand.bid * (idx + 1);
                                });
}
} // namespace part_one