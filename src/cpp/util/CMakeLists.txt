add_executable(sg2_benchmark sg2_benchmark.cpp)
target_link_libraries(sg2_benchmark PRIVATE sg2)
target_include_directories(sg2_benchmark PRIVATE ${sg2_INCLUDE_DIR})

add_executable(sg2_convert_date sg2_convert_date.cpp)
target_link_libraries(sg2_convert_date PRIVATE sg2)
target_include_directories(sg2_convert_date PRIVATE ${sg2_INCLUDE_DIR})

add_executable(sg2_query sg2_query.cpp)
target_link_libraries(sg2_query PRIVATE sg2)
target_include_directories(sg2_query PRIVATE ${sg2_INCLUDE_DIR})