#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "The sum of the game ids of possible games is: "
            << part_one::possible_games(input::day02) << "\n";
  std::cout << "The total game power is: " << part_two::game_powah(input::day02)
            << "\n";
}