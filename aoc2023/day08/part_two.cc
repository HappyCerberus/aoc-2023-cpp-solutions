module;

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <span>
#include <spanstream>
#include <unordered_map>
#include <utility>
#include <vector>

export module part_two;

import graph;

export namespace part_two {
int64_t steps_with_ghosts(std::span<const char> map) {
  using namespace graph;

  std::ispanstream s(map);
  std::string instructions;
  s >> instructions;
  Graph graph;
  s >> graph;

  auto direction = [](int64_t pos, std::string_view instr) {
    if (instr[pos % instr.size()] == 'L')
      return Graph::Left;
    else
      return Graph::Right;
  };

  int64_t result = 1;
  for (auto ghost : graph.start) {
    std::string current = ghost;
    int64_t steps = 0;
    while (current[2] != 'Z') {
      current = graph.step(current, direction(steps, instructions));
      ++steps;
    }
    // The end of the loop is aligned with the instructions
    if (steps % instructions.length() != 0)
      throw std::runtime_error("Unaligned ghost");
    // The ghost is on a proper loop if it returns to this position after steps
    std::string state = current;
    for (int64_t i = 0; i < steps; ++i)
      current = graph.step(current, direction(i, instructions));
    if (current != state)
      throw std::runtime_error("The ghost is not on a proper loop");
    result = std::lcm(result, steps);
  }

  return result;
}
} // namespace part_two