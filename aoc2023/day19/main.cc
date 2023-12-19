#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "Total value of accept items is : "
            << part_one::total_value_of_accepted_items(input::day19) << "\n";
  std::cout << "The total number of accepted combinations is : "
            << part_two::accepted_combinations(input::day19) << "\n";
}