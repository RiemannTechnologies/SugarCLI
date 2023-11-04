cmake_minimum_required(VERSION 3.23)
project(SugarCLI)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(include/SugarInput)


include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
if(WINDOWS)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
FetchContent_MakeAvailable(googletest)

enable_testing()


add_library(SugarCLI STATIC lib/internal/internal_parser.cpp
        lib/internal/internal_vector_iterator.cpp
        lib/internal/internal_vector_iterator.h)

add_executable(SugarCLITest tests/variable_map_creation.cpp
        tests/vector_state.cpp
        tests/item_parsing_test.cpp)
target_compile_definitions(SugarCLITest PRIVATE GTEST_COLOR=yes)

target_link_libraries(SugarCLI PRIVATE SugarInput)
target_include_directories(SugarCLI PRIVATE lib include/ include/SugarInput/lib/)


target_include_directories(SugarCLITest PRIVATE lib)
target_include_directories(SugarCLITest PRIVATE include/ include/SugarInput/lib/) #this is the worst thing I've ever done
target_link_libraries(SugarCLITest PRIVATE SugarInput gtest_main gmock)
include(GoogleTest)
gtest_discover_tests(SugarCLITest)

