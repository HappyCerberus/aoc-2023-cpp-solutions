#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "The number of energized tiles is : "
            << part_one::energized_tiles(input::day16) << "\n";
  std::cout
      << "The maximum number of energized tiles when starting from sides is : "
      << part_two::energized_from_sides(input::day16) << "\n";
}