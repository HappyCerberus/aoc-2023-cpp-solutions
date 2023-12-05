#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "The closest location for a seed is: "
            << part_one::closest_coordinate(input::day05) << "\n";
  std::cout << "The closest location when treating seeds as ranges is: "
            << part_two::closest_range_location(input::day05) << "\n";
}