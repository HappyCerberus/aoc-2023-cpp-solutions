module;

#include <algorithm>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <istream>
#include <queue>
#include <ranges>
#include <set>
#include <span>
#include <spanstream>
#include <string>
#include <unordered_set>
#include <vector>

export module part_one;

export namespace part_one {
int64_t disjoint_component_sizes(std::span<const char> connections) {
  std::ispanstream s(connections);

  std::unordered_set<std::string> nodes;
  std::unordered_map<std::string, std::unordered_set<std::string>> edges;

  std::string from;
  for (std::string module : std::views::istream<std::string>(s)) {
    if (module.back() == ':') {
      from = module.substr(0, module.length() - 1);
      nodes.insert(from);
    } else {
      edges[from].insert(module);
      edges[module].insert(from);
      nodes.insert(module);
    }
  }

  auto shortest_path = [&](const auto &edges, std::string from,
                           std::string to) {
    std::unordered_set<std::string> visited;
    std::queue<std::vector<std::string>> paths;
    visited.insert(from);
    paths.push(std::vector<std::string>{from});

    while (not paths.empty()) {
      auto path = std::move(paths.front());
      paths.pop();
      if (path.back() == to)
        return path;
      for (auto edge_to : edges.at(path.back())) {
        if (visited.contains(edge_to))
          continue;
        visited.insert(edge_to);
        auto next = path;
        next.push_back(edge_to);
        paths.push(std::move(next));
      }
    }
    return std::vector<std::string>{};
  };

  auto connectivity = [&](std::string from, std::string to) {
    auto edges_copy = edges;
    int64_t result = 0;
    auto path = shortest_path(edges_copy, from, to);
    while (not path.empty()) {
      ++result;
      // remove all edges in the path
      for (auto [edge_from, edge_to] : path | std::views::pairwise) {
        edges_copy[edge_from].erase(edge_to);
        edges_copy[edge_to].erase(edge_from);
      }
      path = shortest_path(edges_copy, from, to);
    }
    return result;
  };

  std::vector<std::pair<std::string, std::string>> pairs;
  for (std::string from : nodes) {
    for (std::string to : nodes) {
      if (from == to)
        continue;
      if (not edges[from].contains(to))
        continue;
      if (connectivity(from, to) == 3) {
        pairs.push_back({from, to});
      }
    }
  }

  // Remove the connecting edges
  for (auto [from, to] : pairs) {
    edges[from].erase(to);
    edges[to].erase(from);
  }

  auto count_nodes = [&](std::string component) {
    std::unordered_set<std::string> visited;
    std::queue<std::string> q;
    q.push(component);
    visited.insert(component);
    while (not q.empty()) {
      auto current = q.front();
      q.pop();
      for (auto edge_to : edges[current]) {
        if (visited.contains(edge_to))
          continue;

        q.push(edge_to);
        visited.insert(edge_to);
      }
    }
    return visited.size();
  };

  return count_nodes(pairs[0].first) * count_nodes(pairs[0].second);
}
} // namespace part_one