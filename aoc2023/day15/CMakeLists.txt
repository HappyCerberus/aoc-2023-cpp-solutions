add_library(day15_input)
target_sources(day15_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day15_one)
target_sources(day15_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day15_one)
add_library(day15_two)
target_sources(day15_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day15_two)

add_executable(day15 main.cc)
target_link_libraries(day15 day15_input day15_one day15_two)