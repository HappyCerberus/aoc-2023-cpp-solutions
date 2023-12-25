#include <iostream>

import input;
import part_one;

int main() {
  std::cout << "The product of the component counts in disconnected parts is : "
            << part_one::disjoint_component_sizes(input::day25) << "\n";
}