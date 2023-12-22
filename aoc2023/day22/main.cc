#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "The number of removable blocks is: "
            << part_one::number_of_removable(input::day22) << "\n";
  std::cout << "The maximum chain achievable by removing a single brick is: "
            << part_two::maximum_chain(input::day22) << "\n";
}