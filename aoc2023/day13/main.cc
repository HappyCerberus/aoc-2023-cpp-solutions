#include <iostream>

import input;
import part_one;
import part_two;

int main() {
  std::cout << "The summarized value of all notes is : "
            << part_one::summarize_notes(input::day13) << "\n";
  std::cout << "The summarized value of all notes with one-bit error is : "
            << part_two::summarize_notes_with_error(input::day13) << "\n";
}