cmake_minimum_required(VERSION 3.5)
project(SimpleJson)

FILE(GLOB SOURCE_FILES src/*.cpp test.cpp)
include_directories(include)
add_library(${PROJECT_NAME} ${SOURCE_FILES})
