add_library(day08_input)
target_sources(day08_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)
add_library(day08_graph)
target_sources(day08_graph PUBLIC FILE_SET CXX_MODULES FILES graph.cc)

add_library(day08_one)
target_sources(day08_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day08_one day08_graph)
add_library(day08_two)
target_sources(day08_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day08_two day08_graph)

add_executable(day08 main.cc)
target_link_libraries(day08 day08_input day08_one day08_two)