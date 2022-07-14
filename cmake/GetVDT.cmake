set(AVX2 ON CACHE BOOL "Use AVX2")
set(FMA  ON CACHE BOOL "Use FMA")

include(FetchContent)
FetchContent_Declare(modern_vdt
    GIT_REPOSITORY https://github.com/mikesongming/vdt.git
    GIT_TAG v0.5.0
)
FetchContent_MakeAvailable(modern_vdt)
