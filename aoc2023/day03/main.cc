#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "The sum of coordinates in the schematic is : "
            << part_one::sum_schematic(input::day03) << "\n";
  std::cout << "The sum of gear ratios in the schematic is : "
            << part_two::gear_ratios(input::day03) << "\n";
}