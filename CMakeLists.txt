cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  example_test
  #tests/assertion_tests.cpp
  #tests/test_fixture_example.cpp
  #tests/death_tests.cpp
  #tests/parameterized_tests.cpp
  #tests/mock_example1.cpp
  #tests/mock_example2.cpp
  tests/mock_example3.cpp
)

target_link_libraries(
  example_test
  GTest::gtest_main
  GTest::gmock
)

add_executable(
  mock_reference1
  tests/mock_reference1/user_service.cpp
  tests/mock_reference1/ut_user_service.cpp
)
target_link_libraries(
  mock_reference1
  GTest::gtest_main
  GTest::gmock
)
target_include_directories(mock_reference1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tests/mock_reference1)

add_executable(
  mock_reference2
  tests/mock_reference2/ut_user_service.cpp
)
target_link_libraries(
  mock_reference2
  GTest::gtest_main
  GTest::gmock
)
target_include_directories(mock_reference2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tests/mock_reference2)

include(GoogleTest)
gtest_discover_tests(example_test)
gtest_discover_tests(mock_reference1)
gtest_discover_tests(mock_reference2)