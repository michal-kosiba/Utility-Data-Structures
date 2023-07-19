cmake_minimum_required(VERSION 3.22.1)

project(UDS)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG v1.13.0
)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR}) 
endif()

add_executable(test test.cpp)
target_link_libraries(test gtest_main gmock_main)