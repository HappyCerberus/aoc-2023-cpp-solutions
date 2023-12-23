add_library(day23_input)
target_sources(day23_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day23_one)
target_sources(day23_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day23_one)
add_library(day23_two)
target_sources(day23_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day23_two)

add_executable(day23 main.cc)
target_link_libraries(day23 day23_input day23_one day23_two)