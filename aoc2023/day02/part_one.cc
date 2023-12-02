module;

#include <algorithm>
#include <iostream>
#include <ranges>
#include <spanstream>

export module part_one;

import parsing;

export namespace part_one {
int64_t possible_games(std::span<const char> games) {
  using namespace parsing;
  std::ispanstream s(games);
  return std::ranges::fold_left(
      std::views::istream<Game>(s), 0z, [](int64_t acc, auto &game) {
        if (game.max[Marble::RED] <= 12 && game.max[Marble::GREEN] <= 13 &&
            game.max[Marble::BLUE] <= 14)
          return acc + game.id;

        return acc;
      });
}
} // namespace part_one