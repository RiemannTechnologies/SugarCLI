cmake_minimum_required(VERSION 3.23)
project(SugarCLI)

set(CMAKE_CXX_STANDARD 20)



add_subdirectory(include/spdlog)
add_subdirectory(include/CLI11)
add_subdirectory(include/SugarInput)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB_RECURSE SOURCES "lib/*.cpp")
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
add_library(SugarCLI SHARED ${SOURCES})

add_executable(SugarCLITest ${TEST_SOURCES})
target_compile_definitions(SugarCLITest PRIVATE GTEST_COLOR=yes)

target_link_libraries(SugarCLI PRIVATE CLI11 spdlog::spdlog SugarInput CLI11::CLI11)
target_include_directories(SugarCLI PRIVATE lib)

target_include_directories(SugarCLITest PRIVATE lib)

target_link_libraries(SugarCLITest PRIVATE gtest_main spdlog::spdlog CLI11::CLI11 SugarCLI SugarInput)
include(GoogleTest)
gtest_discover_tests(SugarCLITest)

