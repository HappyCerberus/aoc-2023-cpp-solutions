add_library(day05_input)
target_sources(day05_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day05_one)
target_sources(day05_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day05_one)
add_library(day05_two)
target_sources(day05_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day05_two)

add_executable(day05 main.cc)
target_link_libraries(day05 day05_input day05_one day05_two)