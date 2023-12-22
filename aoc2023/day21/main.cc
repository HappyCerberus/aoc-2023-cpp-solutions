#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "Total plots reachable in exactly 64 steps : "
            << part_one::number_of_plots(input::day21, 64) << "\n";
  std::cout << "Total plots reachable plots on infinite map : "
            << part_two::number_of_plots_on_infinite_map(input::day21, 26501365)
            << "\n";
}