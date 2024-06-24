
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(test_util test_util.cpp)
target_link_libraries(test_util gtest_main fileutil)

include(GoogleTest)
gtest_discover_tests(test_util)
