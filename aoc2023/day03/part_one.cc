module;

#include <algorithm>
#include <ranges>
#include <string_view>
#include <vector>

export module part_one;

export namespace part_one {
int64_t sum_schematic(std::string_view schematic) {
  // Preprocess the input so we are working with a 2D matrix
  std::vector<std::string_view> lines;
  std::ranges::transform(
      schematic | std::views::split('\n'), std::back_inserter(lines),
      [](auto &&rng) { return std::string_view(rng.begin(), rng.end()); });

  // Helper that checks the position for special character and also handles
  // corner cases.
  auto isspecial = [&](int64_t row, int64_t col) {
    if (row < 0 || col < 0)
      return false;
    if (row >= std::ssize(lines) || col >= std::ssize(lines[row]))
      return false;
    return not std::isdigit(lines[row][col]) && lines[row][col] != '.';
  };

  int64_t sum = 0;
  for (int64_t row = 0; row < std::ssize(lines); ++row) {
    // Have we seen a special character on the previous column?
    bool last = false;

    // Currently parsed number
    int64_t number = 0;
    // Is the number valid (i.e. it has a special character next to it)
    bool valid = false;

    for (int64_t col = 0; col < std::ssize(lines[row]); ++col) {
      // Is there a special character on the current column?
      bool current = isspecial(row, col) || isspecial(row - 1, col) ||
                     isspecial(row + 1, col);

      // Parse the digit
      if (isdigit(lines[row][col])) {
        valid |= last || current;
        number *= 10;
        number += lines[row][col] - '0';
      } else if (number != 0) {
        // We are done parsing, check the current column.
        valid |= current;
        // If the number is valid, add it to the total.
        if (valid)
          sum += number;

        // Reset
        number = 0;
        valid = false;
      }

      last = current;
    }
    // Don't forget that we can also finish parsing by running into end of line.
    if (number != 0 && valid)
      sum += number;
  }
  return sum;
}
} // namespace part_one