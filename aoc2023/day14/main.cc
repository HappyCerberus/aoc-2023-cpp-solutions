#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "Total load after sliding north is : "
            << part_one::total_load(input::day14) << "\n";
  std::cout << "Total load after 1'000'000'000 iterations is : "
            << part_two::simulate(input::day14) << "\n";
}