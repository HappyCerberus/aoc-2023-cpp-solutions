add_library(day01_input)
target_sources(day01_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)
add_library(day01_one)
target_sources(day01_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
add_library(day01_two)
target_sources(day01_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)

add_executable(day01 main.cc)
target_link_libraries(day01 day01_input day01_one day01_two)