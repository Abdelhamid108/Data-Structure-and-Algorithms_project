cmake_minimum_required(VERSION 3.16)
project(LibraryManagementSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(library_app
    main.cpp
    src/BooksManage.cpp
    src/DoublyLinked_list.cpp
    src/book.cpp
)

target_include_directories(library_app PRIVATE include)

option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_executable(library_tests tests/test_library.cpp src/DoublyLinked_list.cpp src/book.cpp)
    target_include_directories(library_tests PRIVATE include)
    add_test(NAME library_tests COMMAND library_tests)
endif()
