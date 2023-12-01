#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "The sum of calibration values is: " << part_one::calibration_values(input::day01) << "\n";
  std::cout << "The sum of calibration values with spelled out digits is: " << part_two::spelled_out(input::day01) << "\n";
}