#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "The sum of distances for all galaxies after expansion is: "
            << part_one::sum_of_distances(input::day11) << "\n";
  std::cout << "The sum of distances for all galaxies in an old universe after "
               "expansion is: "
            << part_two::sum_of_distances_old_universe(input::day11) << "\n";
}