add_library(day19_input)
target_sources(day19_input PUBLIC FILE_SET CXX_MODULES FILES input.cc)

add_library(day19_one)
target_sources(day19_one PUBLIC FILE_SET CXX_MODULES FILES part_one.cc)
target_link_libraries(day19_one)
add_library(day19_two)
target_sources(day19_two PUBLIC FILE_SET CXX_MODULES FILES part_two.cc)
target_link_libraries(day19_two)

add_executable(day19 main.cc)
target_link_libraries(day19 day19_input day19_one day19_two)