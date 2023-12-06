#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "The number of ways we can beat the record multiplied for each "
               "course is: "
            << part_one::product_of_number_of_solutions(input::day06) << "\n";

  std::cout << "The number of ways we can beat the record is: "
            << part_two::one_solution(input::day06) << "\n";
}