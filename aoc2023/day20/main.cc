#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "Total pulses sent after 1000 pushes of the button : "
            << part_one::total_pulses(input::day20) << "\n";
  std::cout
      << "Minimum number of button presses to send only one low signal to rx : "
      << part_two::minimum_pulses(input::day20) << "\n";
}