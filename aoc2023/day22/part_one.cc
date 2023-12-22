module;

#include <algorithm>
#include <cstdint>
#include <deque>
#include <iostream>
#include <ranges>
#include <set>
#include <span>
#include <spanstream>
#include <string>
#include <unordered_set>
#include <vector>

export module part_one;

namespace {
struct Skip {
  friend std::istream &operator>>(std::istream &s, Skip) { return s.ignore(); }
};
struct Coord {
  int64_t x;
  int64_t y;
  auto operator<=>(const Coord &) const = default;
};
struct Shape {
  std::pair<int64_t, int64_t> x;
  std::pair<int64_t, int64_t> y;
  std::pair<int64_t, int64_t> z;
  std::set<int64_t> supported_by;
  std::set<int64_t> supports;
  std::pair<Coord, Coord> footprint() const {
    return {{x.first, y.first}, {x.second, y.second}};
  }
  void drop_to(int64_t height) {
    if (z.first < height)
      throw std::runtime_error("Dropping up");
    int64_t offset = z.first - height;
    z.first -= offset;
    z.second -= offset;
  }
  int64_t max_z() const { return z.second; }
  friend std::istream &operator>>(std::istream &s, Shape &shape) {
    return s >> shape.x.first >> Skip{} >> shape.y.first >> Skip{} >>
           shape.z.first >> Skip{} >> shape.x.second >> Skip{} >>
           shape.y.second >> Skip{} >> shape.z.second;
  }
};
} // namespace

template <> struct std::hash<Coord> {
  std::size_t operator()(const Coord &c) const noexcept {
    std::size_t h1 = std::hash<int64_t>{}(c.x);
    std::size_t h2 = std::hash<int64_t>{}(c.y);
    return h1 ^ (h2 << 1);
  }
};

export namespace part_one {
int64_t number_of_removable(std::span<const char> snapshots) {
  std::ispanstream s(snapshots);
  std::deque<Shape> shapes;

  // Parse the shapes
  std::ranges::copy(std::views::istream<Shape>(s), std::back_inserter(shapes));
  // Sort the shapes by z coordinate
  std::ranges::sort(shapes, std::less<>{},
                    [](const Shape &shape) { return shape.z.first; });
  // Calculate the x-y 2D footprint
  auto footprint =
      std::ranges::fold_left(shapes, std::pair{Coord{0, 0}, Coord{0, 0}},
                             [](auto acc, const Shape &shape) {
                               auto current = shape.footprint();
                               return std::pair<Coord, Coord>{
                                   {std::min(acc.first.x, current.first.x),
                                    std::min(acc.first.y, current.first.y)},
                                   {std::max(acc.second.x, current.second.x),
                                    std::max(acc.second.y, current.second.y)}};
                             });

  // Add the floor
  shapes.push_front(Shape{{footprint.first.x, footprint.second.x},
                          {footprint.first.y, footprint.second.y},
                          {0, 0},
                          {},
                          {}});

  // Keep track of the piece with the highest z value for each space
  int64_t xdim = footprint.second.x - footprint.first.x + 1;
  int64_t ydim = footprint.second.y - footprint.first.y + 1;
  std::vector<std::vector<int64_t>> top(xdim, std::vector<int64_t>(ydim, 0));

  // Drop the pieces (skip the floor)
  for (const auto &[idx, shape] :
       shapes | std::views::enumerate | std::views::drop(1)) {

    std::set<int64_t> will_land_on;
    auto [low, high] = shape.footprint();
    // Figure out the set of supporting pieces for this piece
    for (int64_t x = low.x; x < high.x + 1; ++x) {
      for (int64_t y = low.y; y < high.y + 1; ++y) {
        int64_t top_piece = top[x][y];
        if (not will_land_on.empty() &&
            shapes[top_piece].max_z() > shapes[*will_land_on.begin()].max_z())
          will_land_on.clear();
        if (will_land_on.empty() ||
            shapes[top_piece].max_z() == shapes[*will_land_on.begin()].max_z())
          will_land_on.insert(top_piece);
      }
    }
    shape.supported_by = will_land_on; // store

    // Drop and make it the top piece in its footprint
    shape.drop_to(shapes[*will_land_on.begin()].max_z() + 1);
    for (int64_t x = low.x; x < high.x + 1; ++x)
      for (int64_t y = low.y; y < high.y + 1; ++y)
        top[x][y] = idx;
  }

  // We have computed the "supported by" direction.
  // Now translate this into the opposite direction.
  for (auto &&[idx, shape] :
       shapes | std::views::enumerate | std::views::drop(1))
    for (const auto &supported_by : shape.supported_by)
      shapes[supported_by].supports.insert(idx);

  // A piece can be removed if all pieces that it supports have more than one
  // suppport.
  auto can_remove = [&](int64_t idx) {
    return std::ranges::all_of(
        shapes[idx].supports,
        // More than one supporting piece
        [](int64_t count) { return count > 1; },
        // Number supporting pieces
        [&](int64_t idx) { return std::ssize(shapes[idx].supported_by); });
  };
  return std::ranges::count_if(std::views::iota(1z, std::ssize(shapes)),
                               can_remove);
}
} // namespace part_one