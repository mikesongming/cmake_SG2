FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  # GIT_TAG        v2.13.9 # or a later release
  GIT_TAG        v3.1.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

# target_link_libraries(tests Catch2::Catch2WithMain)
