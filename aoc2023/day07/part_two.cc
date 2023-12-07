module;

#include <algorithm>
#include <ranges>
#include <span>
#include <spanstream>
#include <utility>
#include <vector>

export module part_two;

namespace {
struct Card {
  enum Type {
    Joker,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Queen,
    King,
    Ace
  } value;

  auto operator<=>(const Card &other) const = default;
  friend std::istream &operator>>(std::istream &s, Card &card) {
    while (std::isspace(s.peek()))
      s.ignore();
    switch (s.get()) {
    case 'J':
      card.value = Joker;
      break;
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
    // Special case, all jokers
    if (sorted_cards[0].value == Card::Joker) {
      value = FiveOfKind;
      return;
    }

    std::array<int64_t, 5> freq = {1, 0, 0, 0, 0};
    int64_t jokers = 0;
    auto it = freq.begin();
    for (int i = 1; i < 5; ++i) {
      if (sorted_cards[i].value == Card::Joker) {
        ++jokers;
        continue;
      }
      if (sorted_cards[i - 1] != sorted_cards[i])
        ++it;
      ++*it;
    }
    std::ranges::sort(freq, std::greater<>{});
    if (freq[0] == 5) {
      value = FiveOfKind;
    } else if (freq[0] == 4) {
      if (jokers == 0)
        value = FourOfKind;
      else if (jokers == 1)
        value = FiveOfKind;
    } else if (freq[0] == 3 && freq[1] == 2) {
      value = FullHouse;
    } else if (freq[0] == 3 && freq[1] != 2) {
      if (jokers == 0) {
        value = ThreeOfKind;
      } else if (jokers == 1) {
        value = FourOfKind;
      } else if (jokers == 2) {
        value = FiveOfKind;
      }
    } else if (freq[0] == 2 && freq[1] == 2) {
      if (jokers == 0) {
        value = TwoPair;
      } else if (jokers == 1) {
        value = FullHouse;
      }
    } else if (freq[0] == 2 && freq[1] != 2) {
      if (jokers == 0) {
        value = OnePair;
      } else if (jokers == 1) {
        value = ThreeOfKind;
      } else if (jokers == 2) {
        value = FourOfKind;
      } else if (jokers == 3) {
        value = FiveOfKind;
      }
    } else {
      if (jokers == 0) {
        value = HighCard;
      } else if (jokers == 1) {
        value = OnePair;
      } else if (jokers == 2) {
        value = ThreeOfKind;
      } else if (jokers == 3) {
        value = FourOfKind;
      } else if (jokers == 4) {
        value = FiveOfKind;
      }
    }
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
    auto cmp = value <=> other.value;
    if (std::is_neq(cmp))
      return cmp;
    return cards <=> other.cards;
  }
};
} // namespace

export namespace part_two {
int64_t total_winnings_with_jokers(std::span<const char> hands) {
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
} // namespace part_two