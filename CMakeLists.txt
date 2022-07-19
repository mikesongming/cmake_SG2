cmake_minimum_required(VERSION 3.15)
project(cmake_sg2 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
list(APPEND CMAKE_C_FLAGS "-O3")
list(APPEND CMAKE_CXX_FLAGS "-O3")

include(CMakePrintHelpers)

include(TestBigEndian)
test_big_endian(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
    message(FATAL_ERROR "System is of Big Endian")
else()
    message(STATUS "IS_BIG_ENDIAN=${IS_BIG_ENDIAN}, little endian")
endif(IS_BIG_ENDIAN)

find_program(NASM_FOUND nasm
    REGISTRY_VIEW 64
    REQUIRED)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    message(STATUS "Set up ccache ...")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache) # Less useful to do it for linking, see edit2
endif(CCACHE_FOUND)

# Fetch third-party libraries
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "Disable updating fetched content")
include(GetPybind11)
include(GetVDT)

set(sg2_RESOURCES_DIR "${CMAKE_CURRENT_LIST_DIR}/resources")
# list(APPEND sg2_HEADERS
    
# )

add_subdirectory(src)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    if(BUILD_TESTING)
        add_subdirectory(tests)
    endif(BUILD_TESTING)

    add_test(
        NAME test_import_vdt
        COMMAND $<TARGET_FILE:test_vdt>
    )
endif()
