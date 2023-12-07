add_library(day07_input)
target_sources(day07_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day07_one)
target_sources(day07_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day07_one)
add_library(day07_two)
target_sources(day07_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day07_two)

add_executable(day07 main.cc)
target_link_libraries(day07 day07_input day07_one day07_two)