add_library(day04_input)
target_sources(day04_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day04_one)
target_sources(day04_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day04_one)
add_library(day04_two)
target_sources(day04_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day04_two)

add_executable(day04 main.cc)
target_link_libraries(day04 day04_input day04_one day04_two)