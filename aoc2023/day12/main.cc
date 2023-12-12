#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "The total number of options is : "
            << part_one::sum_of_options(input::day12) << "\n";
  std::cout << "The total number of long options is : "
            << part_two::sum_of_long_options(input::day12) << "\n";
};