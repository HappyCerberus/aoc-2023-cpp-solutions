add_library(day22_input)
target_sources(day22_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day22_one)
target_sources(day22_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day22_one)
add_library(day22_two)
target_sources(day22_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day22_two)

add_executable(day22 main.cc)
target_link_libraries(day22 day22_input day22_one day22_two)