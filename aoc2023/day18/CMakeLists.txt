add_library(day18_input)
target_sources(day18_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day18_one)
target_sources(day18_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day18_one)
add_library(day18_two)
target_sources(day18_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day18_two)

add_executable(day18 main.cc)
target_link_libraries(day18 day18_input day18_one day18_two)