module;

#include <algorithm>
#include <ranges>
#include <spanstream>

export module part_two;

import parsing;

export namespace part_two {
int64_t game_powah(std::span<const char> games) {
  using namespace parsing;
  std::ispanstream s(games);
  return std::ranges::fold_left(
      std::views::istream<Game>(s), 0z,
      [](int64_t acc, auto &game) { return acc + game.power(); });
}
} // namespace part_two