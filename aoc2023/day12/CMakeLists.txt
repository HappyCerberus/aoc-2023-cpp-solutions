add_library(day12_input)
target_sources(day12_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day12_one)
target_sources(day12_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day12_one)
add_library(day12_two)
target_sources(day12_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day12_two)

add_executable(day12 main.cc)
target_link_libraries(day12 day12_input day12_one day12_two)