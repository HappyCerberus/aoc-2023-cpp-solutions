#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "Sum of hashes is : " << part_one::sum_of_hashes(input::day15)
            << "\n";
  std::cout << "The total value of the hashmap is : "
            << part_two::hashmap_value(input::day15) << "\n";
}