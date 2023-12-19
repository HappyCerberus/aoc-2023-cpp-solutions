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

export module part_one;

namespace {
struct Ignore {
  std::string_view str;
  friend std::istream &operator>>(std::istream &s, Ignore ctx) {
    return s.ignore(ctx.str.length());
  }
};

struct Item {
  int64_t x;
  int64_t m;
  int64_t a;
  int64_t s;
  int64_t value() const { return x + m + a + s; }
  friend std::istream &operator>>(std::istream &s, Item &item) {
    return s >> Ignore{"{x="} >> item.x >> Ignore{",m="} >> item.m >>
           Ignore{",a="} >> item.a >> Ignore{",s="} >> item.s >> Ignore{"}\n"};
  }
};

struct Rule {
  std::function<int64_t(const Item &)> project;
  std::function<bool(int64_t)> condition;
  std::string destination;

  friend std::istream &operator>>(std::istream &s, Rule &rule) {
    // Done reading rules
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
      rule.condition = [threshold](int64_t value) { return value < threshold; };
    else
      rule.condition = [threshold](int64_t value) { return value > threshold; };
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

  std::string process(const Item &item) const {
    // Iterate over rules
    for (auto &rule : rules) {
      // Until we find one with no condition
      if (not rule.project || not rule.condition)
        return rule.destination;
      // Or the condition evaluates to true
      if (rule.condition(rule.project(item)))
        return rule.destination;
    }
    return "";
  }
};

} // namespace

export namespace part_one {
int64_t total_value_of_accepted_items(std::span<const char> instructions) {
  std::unordered_map<std::string, Workflow> workflows;
  std::ispanstream s(instructions);
  std::ranges::move(std::views::istream<Workflow>(s) |
                        std::views::transform([](Workflow &w) {
                          std::string label = w.label;
                          return std::pair{label, std::move(w)};
                        }),
                    std::inserter(workflows, workflows.end()));
  s.clear();
  return std::ranges::fold_left(std::views::istream<Item>(s), 0z,
                                [&](int64_t acc, const Item &item) {
                                  std::string current = "in";
                                  while (current != "A" && current != "R")
                                    current = workflows[current].process(item);
                                  if (current == "A")
                                    return acc + item.value();
                                  else
                                    return acc;
                                });
}
} // namespace part_one