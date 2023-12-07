#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "Total winnings are: " << part_one::total_winnings(input::day07)
            << "\n";
  std::cout << "Total winnings with jokers are: "
            << part_two::total_winnings_with_jokers(input::day07) << "\n";
}