cmake_minimum_required(VERSION 3.10)

project(HexaViewer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(HexaViewer src/test.cpp include/FileReader.hpp)

target_include_directories(HexaViewer PUBLIC "${PROJECT_SOURCE_DIR}/include")
