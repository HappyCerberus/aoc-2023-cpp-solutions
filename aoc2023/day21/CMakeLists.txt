add_library(day21_input)
target_sources(day21_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day21_one)
target_sources(day21_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day21_one)
add_library(day21_two)
target_sources(day21_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day21_two)

add_executable(day21 main.cc)
target_link_libraries(day21 day21_input day21_one day21_two)