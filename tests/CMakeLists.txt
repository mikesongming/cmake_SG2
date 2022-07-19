# catch main
add_executable(catch2_tests catch2_tests.cpp)
target_link_libraries(catch2_tests PRIVATE Catch2::Catch2)

# test cases
target_sources(catch2_tests PRIVATE test_geocentric_data.cpp)
target_link_libraries(catch2_tests PRIVATE sg2)
target_compile_definitions(catch2_tests PUBLIC "-DSG2_RESOURCES=${sg2_RESOURCES_DIR}")
target_link_directories(catch2_tests INTERFACE ${sg2_CPP_DIR})

# test vdt available
target_sources(catch2_tests PRIVATE test_vdt.cpp)
target_link_libraries(catch2_tests PRIVATE vdt::vdt)
