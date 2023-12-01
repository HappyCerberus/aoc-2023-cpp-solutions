module;

#include <ranges>
#include <algorithm>
#include <string_view>
#include <cctype>

export module part_one;

export namespace part_one {
int64_t calibration_values(std::string_view document) {
    constexpr auto isntdigit = [](char c){ return !isdigit(c); };
    constexpr auto first_digit = std::views::drop_while(isntdigit);
    constexpr auto last_digit = std::views::reverse | first_digit;

    // Treat the first element of a range of character as a decimal digit
    constexpr auto decimal = [](auto&& rng) -> int64_t { return *rng.begin() - '0'; };
    
    // Accumulate the converted calibration values
    return std::ranges::fold_left(document | std::views::split('\n'), 0z,
        [&](int64_t acc, auto&& line) {
            return acc + 
                decimal(line | first_digit) * 10 + 
                decimal(line | last_digit);
        });
}
}