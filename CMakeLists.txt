cmake_minimum_required(VERSION 3.8)
project(clientTest)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp clientHelpers.cpp clientHelpers.h ColorDefs.h)
add_executable(clientTest ${SOURCE_FILES} ColorDefs.h)