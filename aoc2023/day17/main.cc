#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "The minimum total loss is : "
            << part_one::minimum_heatloss(input::day17) << "\n";
  std::cout << "The minimum total loss with heavy crucibles is : "
            << part_two::minimum_heatloss_with_heavy_crucibles(input::day17)
            << "\n";
}