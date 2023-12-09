#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "Sum of predictions is: "
            << part_one::sum_of_predictions(input::day09) << "\n";
  std::cout << "Sum of backwards predictions is: "
            << part_two::sum_of_backwards_predictions(input::day09) << "\n";
}