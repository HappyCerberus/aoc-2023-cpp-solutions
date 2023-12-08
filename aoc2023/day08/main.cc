#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "Number of steps to reach the destination is: "
            << part_one::steps(input::day08) << "\n";
  std::cout << "Number of steps for all ghosts to reach the destination: "
            << part_two::steps_with_ghosts(input::day08) << "\n";
}