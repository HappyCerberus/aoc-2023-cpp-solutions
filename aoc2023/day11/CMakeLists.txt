add_library(day11_input)
target_sources(day11_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day11_one)
target_sources(day11_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day11_one)
add_library(day11_two)
target_sources(day11_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day11_two)

add_executable(day11 main.cc)
target_link_libraries(day11 day11_input day11_one day11_two)