module;

#include <algorithm>
#include <iostream>
#include <ranges>
#include <span>
#include <spanstream>
#include <vector>

export module part_one;

namespace {
struct Range {
  int64_t input_offset;
  int64_t output_offset;
  int64_t size;
  bool operator<(const Range &other) const {
    return input_offset < other.input_offset;
  }
  friend std::istream &operator>>(std::istream &s, Range &rng) {
    return s >> rng.output_offset >> rng.input_offset >> rng.size;
  }
};

struct Mapper {
  std::vector<int64_t> seeds;
  std::vector<Range> seed_to_soil;
  std::vector<Range> soil_to_fertilizer;
  std::vector<Range> fertilizer_to_water;
  std::vector<Range> water_to_light;
  std::vector<Range> light_to_temperature;
  std::vector<Range> temperature_to_humidity;
  std::vector<Range> humidity_to_location;

  static int64_t convert(int64_t input, const std::vector<Range> &map) {
    // Get the relevant mapping
    auto it = std::ranges::upper_bound(map, Range{input, 0, 0}, std::less<>{});
    // If there is none, then no conversion
    if (it == map.begin())
      return input;
    it = std::prev(it);

    // If we are outside the bounds of the relevant mapping, then no conversion
    if (input - it->input_offset > it->size)
      return input;
    // Converted value
    return (input - it->input_offset) + it->output_offset;
  }

  int64_t seed_to_location(int64_t seed) const {
    int64_t soil = convert(seed, seed_to_soil);
    int64_t fertilizer = convert(soil, soil_to_fertilizer);
    int64_t water = convert(fertilizer, fertilizer_to_water);
    int64_t light = convert(water, water_to_light);
    int64_t temperature = convert(light, light_to_temperature);
    int64_t humidity = convert(temperature, temperature_to_humidity);
    return convert(humidity, humidity_to_location);
  }

  friend std::istream &operator>>(std::istream &s, Mapper &mapper) {
    std::string dump;
    s >> dump;

    auto drop_text = [&] {
      while (not std::isdigit(s.peek()))
        s.ignore();
    };

    // Parse the seeds
    std::ranges::copy(std::views::istream<int64_t>(s),
                      std::back_inserter(mapper.seeds));
    s.clear();
    drop_text();
    // Parse the seed-to-soil map
    std::ranges::copy(std::views::istream<Range>(s),
                      std::back_inserter(mapper.seed_to_soil));
    s.clear();
    drop_text();
    // Parse the soil-to-fertilizer map
    std::ranges::copy(std::views::istream<Range>(s),
                      std::back_inserter(mapper.soil_to_fertilizer));
    s.clear();
    drop_text();
    // Parse the fertilizer-to-water map
    std::ranges::copy(std::views::istream<Range>(s),
                      std::back_inserter(mapper.fertilizer_to_water));
    s.clear();
    drop_text();
    // Parse the water-to-light map
    std::ranges::copy(std::views::istream<Range>(s),
                      std::back_inserter(mapper.water_to_light));
    s.clear();
    drop_text();
    // Parse the light_to_temperature map
    std::ranges::copy(std::views::istream<Range>(s),
                      std::back_inserter(mapper.light_to_temperature));
    s.clear();
    drop_text();
    // Parse the temperature-to-humidity map
    std::ranges::copy(std::views::istream<Range>(s),
                      std::back_inserter(mapper.temperature_to_humidity));
    s.clear();
    drop_text();
    // Parse the humidity-to-location map
    std::ranges::copy(std::views::istream<Range>(s),
                      std::back_inserter(mapper.humidity_to_location));
    s.clear();

    // Sort all the maps
    std::ranges::sort(mapper.seed_to_soil, std::less<>{});
    std::ranges::sort(mapper.soil_to_fertilizer, std::less<>{});
    std::ranges::sort(mapper.fertilizer_to_water, std::less<>{});
    std::ranges::sort(mapper.water_to_light, std::less<>{});
    std::ranges::sort(mapper.light_to_temperature, std::less<>{});
    std::ranges::sort(mapper.temperature_to_humidity, std::less<>{});
    std::ranges::sort(mapper.humidity_to_location, std::less<>{});
    return s;
  }
};
} // namespace

export namespace part_one {
int64_t closest_coordinate(std::span<const char> almanac) {
  Mapper map;
  std::ispanstream s(almanac);
  if (not(s >> map))
    throw std::runtime_error("Failed to parse");
  // Minimum location
  return std::ranges::min(map.seeds | std::views::transform([&](int64_t seed) {
                            return map.seed_to_location(seed);
                          }));
}
} // namespace part_one