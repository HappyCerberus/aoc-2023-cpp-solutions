module;

#include <algorithm>
#include <ranges>
#include <span>
#include <spanstream>
#include <utility>
#include <vector>

export module part_one;

export namespace part_one {
int64_t sum_of_predictions(std::span<const char> histogram) {
  // The step between two elements is right-left
  auto step = [](int64_t l, int64_t r) { return r - l; };

  // Prediction for a single line
  auto predict = [&](auto line) {
    std::ispanstream s(line);

    // Our input
    std::vector<int64_t> last;
    std::ranges::copy(std::views::istream<int64_t>(s),
                      std::back_inserter(last));

    // Memorize the last element from each analysis step
    std::vector<int64_t> tails;
    tails.push_back(last.back());

    do {
      // The next step is the mirrored pairwise difference
      // I.e. right-left for each pair of elements
      std::vector<int64_t> next;
      std::ranges::copy(last | std::views::pairwise_transform(step),
                        std::back_inserter(next));

      // If all elements are zero, we are done
      if (std::ranges::all_of(next, [](int64_t v) { return v == 0; }))
        break;

      // Memorize the last element from each analysis step
      tails.push_back(next.back());
      last = std::move(next);
    } while (true);

    // The prediction is the sum of the memorized last elements
    return std::ranges::fold_left(tails, 0z, std::plus<>{});
  };

  // Sum for all lines
  return std::ranges::fold_left(histogram | std::views::split('\n') |
                                    std::views::transform(predict),
                                0z, std::plus<>{});
}
} // namespace part_one