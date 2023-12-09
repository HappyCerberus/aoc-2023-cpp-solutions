add_library(day09_input)
target_sources(day09_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day09_one)
target_sources(day09_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day09_one)
add_library(day09_two)
target_sources(day09_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day09_two)

add_executable(day09 main.cc)
target_link_libraries(day09 day09_input day09_one day09_two)