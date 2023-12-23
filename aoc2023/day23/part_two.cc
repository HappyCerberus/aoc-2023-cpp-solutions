module;

#include <algorithm>
#include <cstdint>
#include <deque>
#include <functional>
#include <queue>
#include <ranges>
#include <set>
#include <span>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

export module part_two;

namespace {
struct Coord {
  int64_t row;
  int64_t col;
  auto operator<=>(const Coord &) const = default;
  Coord operator+(const Coord &other) const {
    return {row + other.row, col + other.col};
  }
};
} // namespace

template <> struct std::hash<Coord> {
  std::size_t operator()(const Coord &c) const noexcept {
    std::size_t h1 = std::hash<int64_t>{}(c.row);
    std::size_t h2 = std::hash<int64_t>{}(c.col);
    return h1 ^ (h2 << 1);
  }
};

namespace {
struct Graph {
  std::unordered_set<Coord> nodes;
  std::unordered_map<Coord, std::unordered_map<Coord, int64_t>> edges;
};

void dfs(const Graph &map, Coord exit, int64_t &max, Coord current,
         int64_t distance, std::unordered_set<Coord> &visited) {
  if (current == exit) {
    max = std::max(max, distance);
    return;
  }
  for (auto &[coord, steps] : map.edges.at(current)) {
    if (visited.contains(coord))
      continue;
    visited.insert(coord);
    dfs(map, exit, max, coord, distance + steps, visited);
    visited.erase(coord);
  }
}
int64_t dfs(const Graph &map, Coord start, Coord exit) {
  std::unordered_set<Coord> visited;
  visited.insert(start);
  int64_t result = 0;
  dfs(map, exit, result, start, 0, visited);
  return result;
}
} // namespace

namespace {
struct State {
  Coord position;
  Coord from;
};

Graph translate(std::span<std::string_view> map, Coord start, Coord exit) {
  Graph result;
  std::unordered_set<Coord> visited;
  std::queue<State> q;

  auto can_step = [&](Coord coord) {
    if (coord.row < 0)
      return false;
    if (coord.col < 0)
      return false;
    if (coord.row >= std::ssize(map))
      return false;
    if (coord.col >= std::ssize(map[coord.row]))
      return false;
    if (map[coord.row][coord.col] == '#')
      return false;
    return true;
  };

  // Helper that provides the upto four steppable neihbours of a space
  auto get_neighbours = [&](Coord pos) {
    std::vector<Coord> result;
    for (auto dir : {Coord{0, 1}, Coord{0, -1}, Coord{1, 0}, Coord{-1, 0}})
      if (can_step(pos + dir))
        result.push_back(pos + dir);
    return result;
  };

  // Eager exploration helper, find the node on the other side of a path and
  // calculate the distance.
  auto next_node = [&](Coord from, Coord coord) {
    auto eager_step = [&](Coord from, std::vector<Coord> &options) {
      for (auto coord : options)
        if (coord != from)
          return coord;
      throw std::runtime_error("Run into a dead-end");
    };

    int64_t distance = 1;
    auto neighbours = get_neighbours(coord);
    while (neighbours.size() <= 2 && coord != exit && coord != start) {
      from = std::exchange(coord, eager_step(from, neighbours));
      ++distance;
      neighbours = get_neighbours(coord);
    }
    return std::pair{coord, distance};
  };

  // First step, going from start to the next space
  q.push({{start.row + 1, start.col}, start});
  visited.insert(start);
  result.nodes.insert(start);

  while (not q.empty()) {
    auto [pos, from] = q.front();
    q.pop();

    // Find the other side of the path
    auto [to, distance] = next_node(from, pos);
    // Record in the graph
    result.nodes.insert(to);
    result.edges[to][from] = distance;
    result.edges[from][to] = distance;

    // If we have already visited this crossroad, do not explore
    if (visited.contains(to))
      continue;
    visited.insert(to);

    // Explore in all four directions
    auto neighbours = get_neighbours(to);
    for (auto coord : neighbours)
      q.push({coord, to});
  }
  return result;
}
} // namespace

export namespace part_two {
int64_t longest_scenic_route_with_good_shoes(std::span<const char> map) {
  std::vector<std::string_view> grid;
  std::ranges::transform(map | std::views::split('\n'),
                         std::back_inserter(grid),
                         [](auto &&rng) { return std::string_view(rng); });

  Coord start = {0, 1};
  Coord exit = {std::ssize(grid) - 1, std::ssize(grid[0]) - 2};
  Graph graph = translate(grid, start, exit);
  return dfs(graph, start, exit);
}
} // namespace part_two