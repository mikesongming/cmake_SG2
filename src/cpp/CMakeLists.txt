enable_language(ASM_NASM)

string(APPEND CMAKE_ASM_NASM_FLAGS "-I ${sg2_RESOURCES_DIR}" " ")

if(APPLE)
    string(APPEND CMAKE_ASM_NASM_FLAGS "--prefix _" " ")
endif()

cmake_print_variables(CMAKE_ASM_NASM_FLAGS)

add_library(sg2 STATIC)
add_library(sg2::sg2 ALIAS sg2)
target_sources(sg2
    INTERFACE sg2_geocentric_data.hpp sg2_utils.h
    PRIVATE sg2_geocentric_data.asm
    sg2.cpp sg2_date.cpp sg2_utils.cpp
    sg2_geopoint.cpp sg2_geocentric.cpp
    sg2_topocentric.cpp
)
target_include_directories(sg2
    PUBLIC $<BUILD_INTERFACE:${sg2_INCLUDE_DIR}>$<INSTALL_INTERFACE:include/sg2>
    PRIVATE $<BUILD_INTERFACE:${sg2_CPP_DIR}>
)
set_target_properties(sg2 PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    PUBLIC_HEADER "${sg2_HEADERS}"
    VERSION "{PROJECT_VERSION}"
)
if(sg2_USE_VDT)
    target_compile_definitions(sg2 PUBLIC "-DSG2_HAVE_VDT")
    target_link_libraries(sg2 PRIVATE vdt::vdt)
endif()