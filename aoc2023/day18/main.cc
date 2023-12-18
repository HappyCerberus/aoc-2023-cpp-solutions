#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "The size of the lagoon is : "
            << part_one::lagoon_size(input::day18) << "\n";
  std::cout << "The size of the big lagoon is : "
            << part_two::big_lagoon_size(input::day18) << "\n";
}