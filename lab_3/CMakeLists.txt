cmake_minimum_required(VERSION 3.10)
project(lab_3 CXX)

# Установка стандарта C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Опции компиляции
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Включаем директорию с заголовочными файлами
include_directories(include)

# Исходные файлы библиотеки
set(LIBRARY_SOURCES
    src/triangle.cpp
    src/hexagon.cpp
    src/octagon.cpp
    src/array.cpp
)

# Создаем статическую библиотеку
add_library(geometry_lib STATIC ${LIBRARY_SOURCES})

# Основная программа
add_executable(lab3_main src/main.cpp)
target_link_libraries(lab3_main geometry_lib)

# Включаем тестирование
enable_testing()

# Загрузка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
# Для Windows: предотвращаем перезапись compiler/linker настроек родительского проекта
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Тестовые файлы
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

# Добавляем тесты в CTest
include(GoogleTest)
gtest_discover_tests(lab3_tests)

# Установка
install(TARGETS lab3_main DESTINATION bin)

