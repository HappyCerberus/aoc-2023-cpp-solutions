add_library(day25_input)
target_sources(day25_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day25_one)
target_sources(day25_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day25_one)

add_executable(day25 main.cc)
target_link_libraries(day25 day25_input day25_one)