add_library(day20_input)
target_sources(day20_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day20_one)
target_sources(day20_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day20_one)
add_library(day20_two)
target_sources(day20_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day20_two)

add_executable(day20 main.cc)
target_link_libraries(day20 day20_input day20_one day20_two)