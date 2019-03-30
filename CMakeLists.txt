cmake_minimum_required(VERSION 3.0)
project(ejson)

set(TEST_NAME ejson_test)
FILE(GLOB SOURCE_FILES src/*.cpp)
include_directories(include)
add_library(${PROJECT_NAME} ${SOURCE_FILES})

add_executable(${TEST_NAME} ${SOURCE_FILES} test/test.cpp)