add_library(day16_input)
target_sources(day16_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day16_one)
target_sources(day16_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day16_one)
add_library(day16_two)
target_sources(day16_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day16_two)

add_executable(day16 main.cc)
target_link_libraries(day16 day16_input day16_one day16_two)