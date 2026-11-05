cmake_minimum_required(VERSION 3.14)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # это нужно, чтобы у меня языковой сервер на clang не ругался на отсуствие нормальных инклюдов

project(DataStructuresProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# автоматическое скачивание внешних библиотек
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# вля винды
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()


add_executable(run_tests 
    tests/test_queue.cpp
    tests/test_stack.cpp
    tests/test_forwardlist.cpp
)


target_include_directories(run_tests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
)


target_link_libraries(run_tests PRIVATE 
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_tests)