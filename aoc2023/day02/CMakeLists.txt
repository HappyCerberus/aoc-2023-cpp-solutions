add_library(day02_input)
target_sources(day02_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)
add_library(day02_parsing)
target_sources(day02_parsing PUBLIC FILE_SET CXX_MODULES FILES parsing.cc)

add_library(day02_one)
target_sources(day02_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day02_one day02_parsing)
add_library(day02_two)
target_sources(day02_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day02_two day02_parsing)

add_executable(day02 main.cc)
target_link_libraries(day02 day02_input day02_one day02_two)