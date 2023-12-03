add_library(day03_input)
target_sources(day03_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)
#add_library(day02_parsing)
#target_sources(day02_parsing PUBLIC FILE_SET CXX_MODULES FILES parsing.cc)

add_library(day03_one)
target_sources(day03_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day03_one)
add_library(day03_two)
target_sources(day03_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day03_two)

add_executable(day03 main.cc)
target_link_libraries(day03 day03_input day03_one day03_two)