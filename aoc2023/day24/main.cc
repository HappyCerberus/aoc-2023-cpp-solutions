#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "There are "
            << part_one::planar_intersections(input::day24, 200000000000000,
                                              400000000000000)
            << " intersections in the X-Y plane.\n";
  std::cout << "The initial position of the stone is : "
            << part_two::line_through_all(input::day24) << "\n";
}