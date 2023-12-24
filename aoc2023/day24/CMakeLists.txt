add_library(day24_input)
target_sources(day24_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day24_one)
target_sources(day24_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day24_one)
add_library(day24_two)
target_sources(day24_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day24_two)

add_executable(day24 main.cc)
target_link_libraries(day24 day24_input day24_one day24_two)