add_executable(test_vdt test_vdt.cpp)
target_link_libraries(test_vdt PRIVATE vdt::vdt)

add_executable(test_geometric_data test_geocentric_data.cpp)
target_link_libraries(test_geometric_data PRIVATE sg2)