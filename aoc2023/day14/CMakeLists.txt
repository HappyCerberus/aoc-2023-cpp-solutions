add_library(day14_input)
target_sources(day14_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day14_one)
target_sources(day14_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day14_one)
add_library(day14_two)
target_sources(day14_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day14_two)

add_executable(day14 main.cc)
target_link_libraries(day14 day14_input day14_one day14_two)