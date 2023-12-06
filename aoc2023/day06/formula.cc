module;

#include <cmath>

export module formula;

export namespace formula {
int64_t count_solutions(int64_t time, int64_t distance) {
  // The boat will travel:
  //    hold*(times-hold)
  // We need to solve:
  //    -1*hold*hold + time*hold > distance
  // Therefore we can solve:
  //    -1*hold*hold + time*hold - distance == 0
  // Reminder: a*x*x + b*x + c
  // Solutions: (-b +- sqrt(b*b-4ac)) / 2a

  double max =
      (-time - std::sqrt(time * time - 4 * (-1) * (-distance))) / (2 * (-1));
  double min =
      (-time + std::sqrt(time * time - 4 * (-1) * (-distance))) / (2 * (-1));
  return std::floor(std::nexttoward(max, min)) -
         std::ceil(std::nexttoward(min, max)) + 1;
}
} // namespace formula