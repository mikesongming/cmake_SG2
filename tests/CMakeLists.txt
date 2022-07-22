# catch main
add_executable(sg2_tests catch2_tests.cpp)
target_link_libraries(sg2_tests PRIVATE Catch2::Catch2WithMain)

# test cases
target_sources(sg2_tests PRIVATE test_geocentric_data.cpp)
target_link_libraries(sg2_tests PRIVATE sg2)
target_include_directories(sg2_tests PRIVATE ${sg2_CPP_DIR})
target_compile_definitions(sg2_tests PUBLIC "-DSG2_RESOURCES=${sg2_RESOURCES_DIR}")

# test vdt available
if(sg2_USE_VDT)
    target_sources(sg2_tests PRIVATE test_vdt.cpp)
    target_link_libraries(sg2_tests PRIVATE vdt::vdt)
endif()
