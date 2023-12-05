module;

#include <algorithm>
#include <iostream>
#include <ranges>
#include <span>
#include <spanstream>
#include <vector>

export module part_two;

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

struct SeedRange {
  int64_t start;
  int64_t size;
  bool operator<(const SeedRange &other) const { return start < other.start; }
  friend std::istream &operator>>(std::istream &s, SeedRange &rng) {
    return s >> rng.start >> rng.size;
  }
};

struct Mapper {
  std::vector<SeedRange> seeds;
  std::vector<Range> seed_to_soil;
  std::vector<Range> soil_to_fertilizer;
  std::vector<Range> fertilizer_to_water;
  std::vector<Range> water_to_light;
  std::vector<Range> light_to_temperature;
  std::vector<Range> temperature_to_humidity;
  std::vector<Range> humidity_to_location;

  static std::vector<SeedRange> convert(const std::vector<SeedRange> &input,
                                        const std::vector<Range> &map) {
    std::vector<SeedRange> output;

    // Get the first relevant map
    auto it = std::ranges::upper_bound(map, Range{input[0].start, 0, 0},
                                       std::less<>{});
    if (it != map.begin())
      it = std::prev(it);

    // For each seed range in the input (the ranges are already sorted)
    for (auto [start, size] : input) {
      while (size > 0) {
        if (it == map.end()) {
          // No conversion, no more mappings
          output.push_back({start, size});
          size = 0;
        } else if (start < it->input_offset) {
          // No conversion (initial part of the range not covered by a mapping)
          int64_t actual = std::min(size, it->input_offset - start);
          output.push_back({start, actual});
          start += actual;
          size -= actual;
        } else if (start - it->input_offset >= it->size) {
          // The current mapping is no longer relevant
          ++it;
        } else {
          // Actual conversion
          int64_t actual =
              std::min((it->input_offset + it->size) - start, size);
          output.push_back(
              {start - it->input_offset + it->output_offset, actual});
          start += actual;
          size -= actual;
        }
      }
    }
    std::ranges::sort(output, std::less<>{});
    return output;
  }

  std::vector<SeedRange> all_seed_locations() const {
    auto soil = convert(seeds, seed_to_soil);
    auto fertilizer = convert(soil, soil_to_fertilizer);
    auto water = convert(fertilizer, fertilizer_to_water);
    auto light = convert(water, water_to_light);
    auto temperature = convert(light, light_to_temperature);
    auto humidity = convert(temperature, temperature_to_humidity);
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
    std::ranges::copy(std::views::istream<SeedRange>(s),
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
    std::ranges::sort(mapper.seeds, std::less<>{});
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

export namespace part_two {
int64_t closest_range_location(std::span<const char> almanac) {
  Mapper map;
  std::ispanstream s(almanac);
  if (not(s >> map))
    throw std::runtime_error("Failed to parse");
  return map.all_seed_locations()[0].start;
}
} // namespace part_two