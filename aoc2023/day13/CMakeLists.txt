add_library(day13_input)
target_sources(day13_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day13_one)
target_sources(day13_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day13_one)
add_library(day13_two)
target_sources(day13_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day13_two)

add_executable(day13 main.cc)
target_link_libraries(day13 day13_input day13_one day13_two)