add_library(day10_input)
target_sources(day10_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day10_one)
target_sources(day10_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day10_one)
add_library(day10_two)
target_sources(day10_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day10_two)

add_executable(day10 main.cc)
target_link_libraries(day10 day10_input day10_one day10_two)