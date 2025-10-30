cmake_minimum_required(VERSION 3.10)
project(lab_3 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

include_directories(include)

set(LIBRARY_SOURCES
    src/triangle.cpp
    src/hexagon.cpp
    src/octagon.cpp
    src/array.cpp
)

add_library(geometry_lib STATIC ${LIBRARY_SOURCES})

add_executable(lab3_main src/main.cpp)
target_link_libraries(lab3_main geometry_lib)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(lab3_tests
    tests/test_triangle.cpp
    tests/test_hexagon.cpp
    tests/test_octagon.cpp
    tests/test_array.cpp
)

target_link_libraries(lab3_tests
    geometry_lib
    gtest_main
    gtest
)

include(GoogleTest)
gtest_discover_tests(lab3_tests)

install(TARGETS lab3_main DESTINATION bin)

