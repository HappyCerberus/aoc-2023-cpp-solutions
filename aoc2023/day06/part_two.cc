module;

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <ranges>
#include <span>
#include <spanstream>
#include <vector>

export module part_two;

import formula;

export namespace part_two {
int64_t one_solution(std::span<const char> document) {
  std::vector<int64_t> times;
  std::vector<int64_t> distances;

  // Parse the input
  std::ispanstream s(document);
  auto skip_text = [&] {
    while (not std::isdigit(s.peek()))
      s.ignore();
  };

  auto parse_number = [&] {
    int64_t number = 0;
    while (std::isspace(s.peek()) || std::isdigit(s.peek())) {
      int c = s.get();
      if (!std::isdigit(c))
        continue;
      number *= 10;
      number += c - '0';
    }
    return number;
  };

  skip_text();
  int64_t time = parse_number();
  skip_text();
  int64_t distance = parse_number();

  return formula::count_solutions(time, distance);
}
} // namespace part_two