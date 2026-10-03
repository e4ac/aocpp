cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDARD 23)
project(aocpp)

add_library(aocpp INTERFACE)
target_include_directories(aocpp INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

option(BUILD_TESTS "Build Tests" ${PROJECT_IS_TOP_LEVEL})
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
