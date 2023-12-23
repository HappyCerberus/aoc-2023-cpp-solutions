#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "The most scenic route has "
            << part_one::longest_scenic_route(input::day23) << " steps\n";
  std::cout << "The most scenic route with good shoes has "
            << part_two::longest_scenic_route_with_good_shoes(input::day23)
            << " steps\n";
}