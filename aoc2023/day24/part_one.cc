module;

#include <algorithm>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <istream>
#include <ranges>
#include <set>
#include <span>
#include <spanstream>
#include <string>
#include <unordered_set>
#include <vector>

export module part_one;

namespace {
struct Coord {
  long double x;
  long double y;
  long double z;
  auto operator<=>(const Coord &) const = default;
  friend std::istream &operator>>(std::istream &s, Coord &coord) {
    char delim;
    return s >> coord.x >> delim >> coord.y >> delim >> coord.z;
  }
};
struct Intersection {
  long double x;
  long double y;
};
struct Hailstone {
  Coord position;
  Coord speed;

  std::optional<Intersection> intersection_xy(const Hailstone &other) {
    long double denom = speed.x * other.speed.y - speed.y * other.speed.x;
    if (denom == 0)
      return std::nullopt;
    long double x =
        (position.x * (position.y - speed.y) -
         position.y * (position.x - speed.x)) *
            other.speed.x -
        speed.x * (other.position.x * (other.position.y - other.speed.y) -
                   other.position.y * (other.position.x - other.speed.x));
    long double y =
        (position.x * (position.y - speed.y) -
         position.y * (position.x - speed.x)) *
            other.speed.y -
        speed.y * (other.position.x * (other.position.y - other.speed.y) -
                   other.position.y * (other.position.x - other.speed.x));
    return Intersection{x / denom, y / denom};
  }
  long double time_to_reach(Intersection point) const {
    return (point.x - position.x) / speed.x;
  }

  friend std::istream &operator>>(std::istream &s, Hailstone &hail) {
    char delim;
    return s >> std::skipws >> hail.position >> delim >> hail.speed;
  }
};
} // namespace

export namespace part_one {
int64_t planar_intersections(std::span<const char> notes, int64_t min,
                             int64_t max) {
  std::vector<Hailstone> hailstones;
  std::ispanstream s(notes);
  std::ranges::copy(std::views::istream<Hailstone>(s),
                    std::back_inserter(hailstones));

  // Adjust for better precisison
  for (int64_t first = 0; first < std::ssize(hailstones); ++first) {
    hailstones[first].position.x -= min;
    hailstones[first].position.y -= min;
    hailstones[first].position.z -= min;
  }

  int64_t count = 0;
  for (int64_t first = 0; first < std::ssize(hailstones); ++first) {
    for (int64_t second = first + 1; second < std::ssize(hailstones);
         ++second) {
      auto intersection = hailstones[first].intersection_xy(hailstones[second]);
      // Parallel lines
      if (not intersection)
        continue;
      // Intersection in the past
      if (hailstones[first].time_to_reach(*intersection) < 0 ||
          hailstones[second].time_to_reach(*intersection) < 0)
        continue;
      if (intersection->x < 0 || intersection->x > max - min)
        continue;
      if (intersection->y < 0 || intersection->y > max - min)
        continue;
      ++count;
    }
  }
  return count;
}
} // namespace part_one