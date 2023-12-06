add_library(day06_input)
target_sources(day06_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)
add_library(day06_formula)
target_sources(day06_formula PUBLIC FILE_SET CXX_MODULES FILES formula.cc)

add_library(day06_one)
target_sources(day06_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day06_one day06_formula)
add_library(day06_two)
target_sources(day06_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day06_two day06_formula)

add_executable(day06 main.cc)
target_link_libraries(day06 day06_input day06_one day06_two)