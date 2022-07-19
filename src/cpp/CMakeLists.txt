enable_language(ASM_NASM)

string(APPEND CMAKE_ASM_NASM_FLAGS "-I ${sg2_RESOURCES_DIR}" " ")

if(APPLE)
    string(APPEND CMAKE_ASM_NASM_FLAGS "--prefix _" " ")
endif()

cmake_print_variables(CMAKE_ASM_NASM_FLAGS)

add_library(sg2 STATIC)
add_library(sg2::sg2 ALIAS sg2)
target_sources(sg2
    INTERFACE sg2_geocentric_data.hpp
    PRIVATE sg2_geocentric_data.asm
)
target_include_directories(sg2
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>$<INSTALL_INTERFACE:include/sg2>
)
set_target_properties(sg2 PROPERTIES
    PUBLIC_HEADER "${sg2_HEADERS}"
    VERSION "{PROJECT_VERSION}"
)