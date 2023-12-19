module;

#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <ranges>
#include <span>
#include <spanstream>
#include <string>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <vector>

export module part_two;

namespace {
struct Ignore {
  std::string_view str;
  friend std::istream &operator>>(std::istream &s, Ignore ctx) {
    return s.ignore(ctx.str.length());
  }
};

struct Range {
  int64_t min;
  int64_t max;
  int64_t size() const { return max - min + 1; }
};

struct Item {
  Item() : x{1, 4000}, m{1, 4000}, a{1, 4000}, s{1, 4000} {}
  Range x;
  Range m;
  Range a;
  Range s;
  int64_t combinations() const {
    return x.size() * m.size() * a.size() * s.size();
  }
};

struct Rule {
  std::function<Range &(Item &)> project;
  std::function<std::pair<Range, Range>(Range)> condition;
  std::string destination;
  friend std::istream &operator>>(std::istream &s, Rule &rule) {
    if (s.peek() == '}') {
      s.setstate(std::ios::failbit);
      return s;
    }
    int type = s.get();
    if (type == 'x' && not std::isalnum(s.peek()))
      rule.project = &Item::x;
    else if (type == 'm' && not std::isalnum(s.peek()))
      rule.project = &Item::m;
    else if (type == 'a' && not std::isalnum(s.peek()))
      rule.project = &Item::a;
    else if (type == 's' && not std::isalnum(s.peek()))
      rule.project = &Item::s;
    else {
      // Not a condition, a label
      std::string label{static_cast<char>(type)};
      while (s.peek() != '}')
        label.push_back(s.get());
      rule.project = {};
      rule.condition = {};
      rule.destination = label;
      return s;
    }

    int condition = s.get();
    int64_t threshold;
    s >> threshold >> Ignore{":"};

    std::string label;
    while (s.peek() != '}' && s.peek() != ',')
      label.push_back(s.get());
    if (s.peek() == ',')
      s.ignore();

    if (condition == '<')
      rule.condition = [threshold](Range value) {
        return std::pair{Range{value.min, std::min(threshold - 1, value.max)},
                         Range{std::max(threshold, value.min), value.max}};
      };
    else
      rule.condition = [threshold](Range value) {
        return std::pair{Range{std::max(threshold + 1, value.min), value.max},
                         Range{value.min, std::min(threshold, value.max)}};
      };
    rule.destination = label;
    return s;
  }
};

struct Workflow {
  std::string label;
  std::vector<Rule> rules;

  friend std::istream &operator>>(std::istream &s, Workflow &workflow) {
    // Workflows end with an empty line
    if (s.peek() == '\n') {
      s.ignore();
      s.setstate(std::ios::failbit);
      return s;
    }

    std::string label;
    while (s.peek() != '{')
      label.push_back(s.get());
    workflow.label = label;
    workflow.rules.clear();
    s >> Ignore{"{"};
    std::ranges::move(std::views::istream<Rule>(s),
                      std::back_inserter(workflow.rules));
    s.clear();
    return s >> Ignore{"}\n"};
  }
};

void search(const std::unordered_map<std::string, Workflow> &workflows,
            std::vector<Item> &accepted, std::string label, Item value) {
  // Accepted
  if (label == "A") {
    accepted.push_back(value);
    return;
  }
  // Rejected
  if (label == "R") {
    return;
  }

  // Process the workflow
  for (const Rule &rule : workflows.at(label).rules) {
    // No condition means that we are jumping to a new label
    if (not rule.condition || not rule.project) {
      search(workflows, accepted, rule.destination, value);
      continue;
    }

    // Get the "true" and "false" chunks
    auto [jump, next] = rule.condition(rule.project(value));
    if (jump.size() > 0) {
      // If the "true" chunk contains valid values
      Item new_value = value;
      // Update the relevant member with the values
      rule.project(new_value) = jump;
      // recurse
      search(workflows, accepted, rule.destination, new_value);
    }
    // If the "false" chunk doesn't contain any values, we are done
    if (next.size() <= 0) // dead-end
      break;
    // Otherwise update the relevant member with the "false" values and continue
    rule.project(value) = next;
  }
}
} // namespace

export namespace part_two {
int64_t accepted_combinations(std::span<const char> instructions) {
  std::unordered_map<std::string, Workflow> workflows;
  std::ispanstream s(instructions);
  std::ranges::move(std::views::istream<Workflow>(s) |
                        std::views::transform([](Workflow &w) {
                          std::string label = w.label;
                          return std::pair{label, std::move(w)};
                        }),
                    std::inserter(workflows, workflows.end()));

  std::vector<Item> accepted;
  search(workflows, accepted, "in", {});
  return std::ranges::fold_left(
      accepted, 0z,
      [](int64_t acc, const Item &item) { return acc + item.combinations(); });
}
} // namespace part_two