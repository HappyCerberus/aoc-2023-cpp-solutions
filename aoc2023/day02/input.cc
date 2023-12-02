module;

#include <string_view>

export module input;

export namespace input {
const std::string_view day02 =
    R"(Game 1: 18 red, 8 green, 7 blue; 15 red, 4 blue, 1 green; 2 green, 17 red, 6 blue; 5 green, 1 blue, 11 red; 18 red, 1 green, 14 blue; 8 blue
Game 2: 16 blue, 12 green, 3 red; 13 blue, 2 red, 8 green; 15 green, 3 red, 16 blue
Game 3: 6 green, 15 red; 1 green, 4 red, 7 blue; 9 blue, 7 red, 8 green
Game 4: 8 red, 2 blue; 11 red, 5 blue, 1 green; 12 red, 1 green, 5 blue; 1 blue; 2 blue, 9 red
Game 5: 9 blue, 3 red, 12 green; 3 green, 4 red, 17 blue; 15 blue, 2 green, 5 red; 3 blue, 5 green, 6 red; 6 red, 4 blue, 7 green; 3 green, 10 blue
Game 6: 11 red, 2 blue, 6 green; 2 blue, 9 red, 4 green; 3 blue, 12 red, 8 green; 5 red, 11 green, 4 blue; 2 blue, 9 red, 13 green; 15 red, 3 blue, 7 green
Game 7: 2 red, 9 green, 12 blue; 14 blue, 1 green, 6 red; 7 blue, 9 green; 9 green, 8 red, 4 blue; 5 red, 3 green, 16 blue; 4 red, 8 green
Game 8: 11 red, 12 green, 1 blue; 4 red, 7 green; 11 red, 6 green; 17 green; 15 green, 1 red
Game 9: 1 red, 1 green, 12 blue; 3 green, 12 red, 6 blue; 14 red, 1 blue; 9 blue, 1 red, 3 green
Game 10: 1 red, 4 blue; 3 blue, 4 green; 3 green, 3 red, 8 blue; 2 blue, 3 red; 3 green, 4 red, 3 blue
Game 11: 8 blue, 1 red; 8 green, 1 red, 1 blue; 13 green, 9 red, 6 blue
Game 12: 2 red, 2 blue, 1 green; 3 red, 1 green; 1 blue, 3 green
Game 13: 12 green, 4 blue; 2 red, 2 blue, 8 green; 6 green, 3 red; 3 red, 5 green; 9 green, 7 blue, 1 red
Game 14: 1 red, 7 green; 5 green, 12 red, 10 blue; 9 red, 11 blue, 7 green; 7 blue, 3 red, 9 green
Game 15: 7 green, 1 blue; 1 red, 2 green, 1 blue; 7 green
Game 16: 1 green, 1 blue; 2 blue, 4 green, 2 red; 2 green, 2 blue
Game 17: 6 red, 11 green, 7 blue; 1 blue, 13 green, 4 red; 4 green, 6 blue, 7 red
Game 18: 2 red, 8 blue; 7 red, 11 blue; 1 green, 16 blue, 7 red; 18 blue, 1 green, 14 red
Game 19: 2 red, 2 blue; 1 green, 6 red; 1 green, 3 red, 2 blue
Game 20: 6 red, 2 blue, 5 green; 4 red, 1 blue, 9 green; 3 blue, 2 red, 9 green; 8 red, 12 green, 5 blue
Game 21: 6 red, 7 blue; 3 blue, 16 red, 2 green; 2 blue, 13 red; 3 blue, 11 red, 3 green; 1 green, 18 red, 6 blue; 12 red, 5 blue, 2 green
Game 22: 9 red, 6 blue, 14 green; 1 blue, 5 green, 13 red; 6 red; 18 red, 4 green; 2 blue, 10 green, 16 red; 1 red, 18 green, 1 blue
Game 23: 6 green, 4 red, 3 blue; 1 blue, 2 red, 9 green; 5 green, 1 red, 3 blue; 5 blue, 4 red, 4 green
Game 24: 1 red, 5 green, 2 blue; 4 red, 7 green, 9 blue; 9 blue, 7 green; 7 green, 13 blue; 4 blue, 1 green, 4 red
Game 25: 13 blue, 10 red, 11 green; 10 green, 1 blue, 3 red; 15 red, 5 green, 8 blue; 19 red, 10 green, 13 blue; 12 blue, 4 green, 16 red; 7 red, 5 green, 9 blue
Game 26: 20 red, 6 blue, 12 green; 15 blue, 17 red, 9 green; 19 red, 6 green, 3 blue; 8 green, 1 red, 15 blue; 10 green, 8 red, 5 blue; 4 green, 20 red, 18 blue
Game 27: 2 blue, 3 green, 7 red; 2 blue, 4 red; 5 blue, 5 green; 8 blue, 6 green, 2 red
Game 28: 1 green, 6 red; 3 red, 3 blue; 1 green, 4 red; 1 red, 2 blue; 2 red
Game 29: 8 blue, 1 green; 7 blue, 1 red; 6 red, 2 blue; 2 red, 3 green; 3 red, 6 green, 5 blue
Game 30: 11 blue, 17 green, 10 red; 9 blue, 12 green, 14 red; 16 green, 2 red, 8 blue; 18 green, 1 red, 1 blue; 5 blue, 7 red, 18 green; 9 green, 3 blue, 11 red
Game 31: 5 blue, 13 green; 2 green, 3 red, 4 blue; 3 red, 15 green, 2 blue; 5 blue, 19 green; 5 blue, 18 green; 3 green, 7 blue, 3 red
Game 32: 12 red, 2 green, 3 blue; 2 green, 16 red, 1 blue; 13 red, 4 green, 6 blue
Game 33: 18 green, 8 blue, 3 red; 15 green, 2 blue, 4 red; 14 blue, 3 red, 6 green; 20 green, 13 blue; 1 red, 19 green
Game 34: 1 green, 7 blue, 2 red; 8 green, 10 blue, 2 red; 3 blue, 1 green, 1 red; 6 green, 13 blue, 1 red; 1 green, 4 blue, 2 red; 1 red, 5 green, 7 blue
Game 35: 7 blue, 8 red; 2 blue, 3 red; 4 blue, 3 red; 7 red, 4 blue; 1 blue, 1 green, 3 red
Game 36: 1 red, 8 green; 1 red, 6 green; 3 green, 8 red; 1 blue, 2 red, 1 green
Game 37: 3 blue, 13 red; 2 blue, 7 red; 5 red, 1 green; 3 red, 3 blue; 1 blue, 12 red, 1 green; 14 red, 3 blue
Game 38: 7 blue, 18 red, 12 green; 11 red, 6 green, 1 blue; 9 green, 1 red; 9 green, 13 blue, 16 red
Game 39: 12 red, 3 green, 2 blue; 3 blue, 3 green, 10 red; 2 blue, 5 red; 2 blue, 1 green; 5 blue, 4 green, 7 red; 2 green, 1 red
Game 40: 1 red, 7 blue, 5 green; 1 red, 4 blue, 8 green; 3 red, 5 blue, 14 green; 10 green, 2 blue, 1 red; 11 blue, 7 green, 1 red; 14 green, 2 blue
Game 41: 8 green, 5 red, 3 blue; 5 red, 4 blue, 12 green; 10 green, 6 blue; 13 green, 7 blue; 1 red, 2 green, 15 blue
Game 42: 17 red, 1 blue, 5 green; 9 green, 16 red; 1 blue, 15 green, 2 red; 1 blue, 12 red, 12 green
Game 43: 12 green, 5 blue; 3 red, 8 blue, 10 green; 8 blue, 2 green, 1 red
Game 44: 1 green, 7 red, 2 blue; 1 blue, 10 red; 4 green, 3 blue, 19 red; 1 blue, 3 green, 1 red; 1 blue; 4 red, 2 green, 3 blue
Game 45: 16 red, 12 blue, 1 green; 13 blue, 16 red, 9 green; 7 green, 3 red, 8 blue
Game 46: 1 red, 17 green, 6 blue; 6 blue, 1 red, 3 green; 12 green, 1 blue; 4 blue, 2 green
Game 47: 2 green, 12 red, 15 blue; 9 blue, 2 green, 2 red; 3 green, 6 blue, 2 red; 11 blue, 3 green, 5 red; 6 green, 9 red, 17 blue
Game 48: 5 blue, 6 red; 7 green, 14 red, 4 blue; 2 green, 5 blue, 2 red; 11 blue, 5 red, 5 green
Game 49: 7 green, 7 blue, 4 red; 11 green, 12 blue, 2 red; 12 blue, 4 red, 9 green; 3 red, 8 blue, 17 green; 16 green, 3 red, 14 blue
Game 50: 5 green, 4 red, 10 blue; 7 green, 14 red, 5 blue; 12 red, 18 blue, 14 green
Game 51: 12 green, 3 blue; 10 green, 4 blue, 2 red; 3 green, 5 blue
Game 52: 12 green, 6 red, 7 blue; 20 green, 6 red, 18 blue; 1 green, 5 blue, 11 red; 2 green, 15 blue, 6 red
Game 53: 6 red, 2 green, 5 blue; 13 green, 1 blue, 14 red; 7 green, 1 blue; 3 green, 4 blue, 6 red; 10 red, 6 green, 4 blue
Game 54: 4 blue, 1 red; 1 red, 1 blue, 9 green; 3 red, 2 blue, 4 green; 3 green, 2 red, 5 blue; 9 blue, 2 red, 7 green
Game 55: 7 blue; 6 blue, 1 red; 4 red, 7 blue; 3 red, 3 blue, 1 green
Game 56: 2 green, 7 blue; 3 red, 10 blue; 1 green, 2 red; 3 red, 8 blue, 4 green; 1 green, 11 blue, 3 red; 2 green, 8 blue
Game 57: 3 red, 1 green; 1 green, 1 red, 1 blue; 1 red, 4 green, 15 blue; 9 blue, 2 red, 1 green
Game 58: 12 blue, 13 red, 5 green; 2 blue, 6 green; 12 red, 15 green, 7 blue; 5 red, 4 green, 14 blue; 15 red, 2 green, 9 blue
Game 59: 5 green, 5 blue; 4 red, 6 blue, 2 green; 5 blue, 3 green, 6 red; 3 red, 6 green, 4 blue; 3 blue, 7 green, 10 red
Game 60: 1 red, 1 blue, 3 green; 1 red; 3 green, 6 blue; 6 blue
Game 61: 7 green, 1 red, 1 blue; 4 red, 3 green, 1 blue; 7 blue, 7 green; 11 blue, 2 green, 5 red; 5 red, 4 green, 5 blue
Game 62: 17 green, 2 red, 3 blue; 1 red, 3 blue, 2 green; 1 green, 3 blue, 2 red; 1 red, 17 green; 2 red, 15 green, 4 blue; 5 green
Game 63: 2 green, 4 red, 3 blue; 9 blue, 10 red; 1 green, 13 blue, 2 red; 2 green, 1 blue, 5 red
Game 64: 6 red, 8 blue; 3 red, 6 blue, 5 green; 13 red, 11 blue, 8 green; 11 red, 3 blue, 1 green
Game 65: 4 green, 1 blue, 2 red; 3 blue, 3 green, 11 red; 6 green, 3 blue, 3 red; 5 red, 4 blue; 8 red, 5 blue, 2 green
Game 66: 10 green, 13 red; 1 blue, 2 red, 4 green; 7 red, 7 green; 19 green, 9 red, 1 blue; 16 green, 16 red, 2 blue; 10 red, 11 green
Game 67: 3 blue, 4 green, 2 red; 6 blue, 19 red; 4 blue, 2 red, 5 green; 4 green, 5 blue, 1 red
Game 68: 13 blue, 15 red, 7 green; 5 blue, 20 red; 6 green, 12 blue, 8 red; 5 blue, 8 green
Game 69: 13 red, 13 green; 13 green, 3 red, 1 blue; 8 green; 9 green, 9 red
Game 70: 8 blue, 11 red, 2 green; 12 red, 2 blue; 13 red, 6 blue, 3 green; 7 blue, 3 green, 5 red; 15 red, 1 blue, 3 green
Game 71: 7 red, 9 green; 4 blue, 9 green, 7 red; 4 blue, 2 green; 6 blue, 2 red, 9 green
Game 72: 14 blue, 1 green; 4 red, 1 green, 9 blue; 6 blue, 8 red, 2 green
Game 73: 17 green; 10 blue, 2 red, 9 green; 1 green, 10 blue, 2 red; 8 blue, 1 red; 5 blue, 16 green
Game 74: 12 green, 6 red, 5 blue; 2 red, 4 blue, 10 green; 3 green, 4 blue, 2 red; 8 green, 2 red, 5 blue; 5 red, 2 blue, 2 green; 6 green, 1 red, 1 blue
Game 75: 4 blue, 19 green; 15 blue, 7 green; 18 blue, 5 green, 7 red; 16 green, 15 blue; 7 red, 4 green, 13 blue; 9 green, 13 blue
Game 76: 1 red, 2 green, 7 blue; 13 blue, 7 green, 1 red; 13 blue, 5 red
Game 77: 3 red, 10 blue, 6 green; 1 green, 2 red, 10 blue; 7 green, 1 red
Game 78: 11 green, 2 blue; 6 blue, 8 red, 5 green; 10 red, 6 green, 4 blue; 6 blue, 3 green, 10 red; 5 green, 6 red
Game 79: 4 red, 6 blue, 1 green; 1 red; 2 green, 3 blue, 4 red; 4 red, 1 green, 2 blue; 2 green, 1 red
Game 80: 2 red, 1 green; 1 red, 1 green; 7 red, 1 green; 1 blue, 7 red, 3 green
Game 81: 1 blue, 15 red, 4 green; 2 green, 12 red; 4 green, 13 red; 1 blue, 3 green, 13 red; 12 red, 2 green, 1 blue; 3 green, 8 red, 1 blue
Game 82: 18 red, 4 green, 1 blue; 14 red, 1 green, 2 blue; 10 red, 2 blue, 7 green; 13 red; 3 red, 7 green, 1 blue; 5 red, 4 green
Game 83: 4 red, 10 green, 5 blue; 2 red, 12 blue, 13 green; 19 blue, 9 green, 1 red; 2 red, 14 blue, 3 green; 13 green, 8 blue, 5 red
Game 84: 12 blue, 7 red, 9 green; 1 blue, 1 green, 14 red; 1 green, 8 red, 11 blue; 11 blue, 12 red, 3 green; 11 blue, 8 green, 13 red; 7 green, 7 red, 10 blue
Game 85: 10 red, 2 blue; 11 green, 9 red, 4 blue; 3 red, 5 blue, 13 green; 5 red, 5 green; 5 red, 2 blue, 4 green; 11 green, 4 blue, 19 red
Game 86: 1 blue, 6 green, 2 red; 1 red, 1 blue, 8 green; 3 red, 1 blue, 4 green; 1 green, 4 red; 9 green, 2 red; 6 green, 7 red, 1 blue
Game 87: 8 green, 8 blue, 4 red; 5 red, 2 blue, 10 green; 3 red, 13 green; 1 red, 3 blue, 4 green
Game 88: 3 blue, 9 green, 3 red; 2 blue, 15 green; 2 red, 9 green
Game 89: 9 red, 6 green, 15 blue; 10 blue, 7 red, 2 green; 7 green, 16 blue, 4 red
Game 90: 1 red, 1 blue, 7 green; 7 green, 1 blue, 8 red; 3 red, 1 blue, 1 green
Game 91: 1 green, 2 red, 6 blue; 4 green, 4 red, 3 blue; 4 red, 11 green, 4 blue; 3 blue, 5 red; 8 green, 2 red, 8 blue
Game 92: 2 red, 3 blue; 3 blue, 2 green, 2 red; 9 red, 3 green
Game 93: 2 blue, 5 green; 2 green, 5 blue, 3 red; 2 green, 5 blue, 1 red; 7 blue, 4 red, 9 green
Game 94: 1 red, 9 blue, 14 green; 6 green; 2 blue, 11 green; 4 blue, 16 green, 1 red
Game 95: 10 green, 2 blue, 7 red; 4 blue, 4 red, 6 green; 3 red, 2 blue, 3 green
Game 96: 12 red; 3 green, 10 red; 6 blue, 14 red, 2 green; 7 green, 15 red; 3 green, 3 red, 1 blue; 5 blue, 1 red
Game 97: 3 red, 1 green, 1 blue; 1 green, 3 red; 4 red, 1 green
Game 98: 4 red, 5 green, 6 blue; 2 red, 9 green, 6 blue; 2 blue, 11 red, 14 green; 6 green, 4 blue; 11 blue, 11 red, 8 green
Game 99: 2 green, 20 blue; 12 blue; 3 red, 12 blue; 7 blue; 3 green, 10 blue, 2 red; 3 red, 2 green
Game 100: 2 blue, 8 green, 12 red; 2 green, 13 red; 2 red, 4 green; 2 green, 7 red; 10 green, 5 red, 1 blue)";
const std::string_view day02_test =
    R"(Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green)";
} // namespace input