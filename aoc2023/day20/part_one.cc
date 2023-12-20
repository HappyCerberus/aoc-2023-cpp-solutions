module;

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <ranges>
#include <span>
#include <spanstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

export module part_one;
namespace {
// Parsing helpers
struct ReadAlnum {
  std::string &dest;
  friend std::istream &operator>>(std::istream &s, ReadAlnum &&v) {
    v.dest.clear();
    while (s && std::isalnum(s.peek()))
      v.dest += s.get();
    return s;
  }
};
struct SkipDelim {
  friend std::istream &operator>>(std::istream &s, SkipDelim) {
    while (s && s.peek() != '\n' && not std::isalnum(s.peek()))
      s.ignore();
    return s;
  }
};

struct ConnectionMesh;

struct Signal {
  enum Strength { Low, High } signal;
  std::string from;
  std::string to;
};

struct FlipFlop {
  std::string label;
  Signal::Strength state;
  std::vector<std::string> connections;
  void flip() {
    switch (state) {
    case Signal::Low:
      state = Signal::High;
      break;
    case Signal::High:
      state = Signal::Low;
      break;
    }
  }
  void receive_signal(ConnectionMesh &, Signal::Strength, std::string);
  bool sends_to(const std::string &label) {
    return std::ranges::contains(connections, label);
  }
};

struct Conjunction {
  std::string label;
  std::unordered_map<std::string, Signal::Strength> state;
  std::vector<std::string> connections;
  void receive_signal(ConnectionMesh &, Signal::Strength, std::string);
  bool sends_to(const std::string &label) const {
    return std::ranges::contains(connections, label);
  }
};

struct Button {
  void press(ConnectionMesh &mesh);
};

struct Broadcaster {
  std::string label;
  std::vector<std::string> connections;
  void receive_signal(ConnectionMesh &, Signal::Strength, std::string) const;
  bool sends_to(const std::string &label) const {
    return std::ranges::contains(connections, label);
  }
};

struct ConnectionMesh {
  std::unordered_map<std::string,
                     std::variant<Broadcaster, Conjunction, FlipFlop>>
      modules;
  std::queue<Signal> pending_signals;
  int64_t low_signals = 0;
  int64_t high_signals = 0;

  // Interface for modules
  void send_signal(Signal::Strength signal, std::string from, std::string to) {
    if (signal == Signal::High) {
      pending_signals.push({Signal::High, from, to});
      ++high_signals;
    }
    if (signal == Signal::Low) {
      pending_signals.push({Signal::Low, from, to});
      ++low_signals;
    }
  }

  // Process one signal, by invoking the receive signal method on the target
  // module
  bool process_signal() {
    if (pending_signals.empty())
      return false;
    Signal sig = pending_signals.front();
    pending_signals.pop();
    auto it = modules.find(sig.to);
    if (it == modules.end())
      return true;
    std::visit(
        [&](auto &module) {
          module.receive_signal(*this, sig.signal, sig.from);
        },
        it->second);
    return true;
  }

  friend std::istream &operator>>(std::istream &s, ConnectionMesh &mesh) {
    std::vector<std::string> conjunctions;
    while (s) {
      char type = s.peek();
      if (not std::isalnum(type))
        s.ignore();

      std::string label;
      s >> ReadAlnum{label} >> SkipDelim{};

      std::vector<std::string> dest;
      while (s && s.peek() != '\n') {
        std::string label;
        s >> ReadAlnum{label} >> SkipDelim{};
        dest.push_back(std::move(label));
      }

      switch (type) {
      case '%':
        mesh.modules[label] = FlipFlop{label, Signal::Low, dest};
        break;
      case '&':
        mesh.modules[label] = Conjunction{label, {}, dest};
        conjunctions.push_back(label);
        break;
      default:
        mesh.modules[label] = Broadcaster{label, dest};
        break;
      }
      s.ignore(); // '\n'
    }

    // Post-process step, ensure that all conjuctions are correctly initialized
    for (auto &label : conjunctions) {
      for (auto [other_label, other] : mesh.modules) {
        if (std::visit([&](auto &module) { return module.sends_to(label); },
                       other)) {
          std::get<Conjunction>(mesh.modules[label]).state[other_label] =
              Signal::Low;
        }
      }
    }
    return s;
  }
};

void Button::press(ConnectionMesh &mesh) {
  mesh.send_signal(Signal::Low, "button", "broadcaster");
}

void Broadcaster::receive_signal(ConnectionMesh &mesh, Signal::Strength signal,
                                 std::string) const {
  for (auto &dest : connections)
    mesh.send_signal(signal, label, dest);
}

void Conjunction::receive_signal(ConnectionMesh &mesh, Signal::Strength signal,
                                 std::string from) {
  state[from] = signal;
  auto is_high = [](Signal::Strength sig) { return sig == Signal::High; };
  if (std::ranges::all_of(state | std::views::values, is_high))
    for (auto &dest : connections)
      mesh.send_signal(Signal::Low, label, dest);
  else
    for (auto &dest : connections)
      mesh.send_signal(Signal::High, label, dest);
}

void FlipFlop::receive_signal(ConnectionMesh &mesh, Signal::Strength signal,
                              std::string) {
  if (signal == Signal::Low) {
    flip();
    for (auto &dest : connections)
      mesh.send_signal(state, label, dest);
  }
}
} // namespace

export namespace part_one {
int64_t total_pulses(std::span<const char> diagram) {
  std::ispanstream s(diagram);
  ConnectionMesh mesh;
  s >> mesh;

  Button button;
  int64_t presses = 0;
  while (presses < 1000) {
    button.press(mesh);
    ++presses;
    while (mesh.process_signal())
      ;
  }

  return mesh.low_signals * mesh.high_signals;
}
} // namespace part_one