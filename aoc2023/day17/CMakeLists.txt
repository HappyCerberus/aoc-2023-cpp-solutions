add_library(day17_input)
target_sources(day17_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day17_one)
target_sources(day17_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day17_one)
add_library(day17_two)
target_sources(day17_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day17_two)

add_executable(day17 main.cc)
target_link_libraries(day17 day17_input day17_one day17_two)