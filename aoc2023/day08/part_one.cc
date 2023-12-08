module;

#include <algorithm>
#include <ranges>
#include <span>
#include <spanstream>
#include <unordered_map>
#include <utility>
#include <vector>

export module part_one;

import graph;

export namespace part_one {
int64_t steps(std::span<const char> map) {
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
  std::string start = "AAA";
  std::string end = "ZZZ";

  std::string current = start;
  int64_t steps = 0;
  while (current != end) {
    current = graph.step(current, direction(steps, instructions));
    ++steps;
  }

  return steps;
}
} // namespace part_one