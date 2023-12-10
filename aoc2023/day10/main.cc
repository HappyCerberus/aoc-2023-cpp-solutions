#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "The fartherst point is "
            << part_one::number_of_steps(input::day10) << " steps away\n";
  std::cout << "The number of encricled spaces is: "
            << part_two::encircled_spaces(input::day10) << "\n";
}