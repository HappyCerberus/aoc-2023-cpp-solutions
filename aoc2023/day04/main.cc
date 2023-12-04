#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "The total score for all scratchcards is: "
            << part_one::total_score(input::day04) << '\n';
  std::cout << "Total number of scratchcards is: "
            << part_two::total_scratchcards(input::day04) << '\n';
}