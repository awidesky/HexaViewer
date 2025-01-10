cmake_minimum_required(VERSION 3.10)

project(HexaViewer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test src/test.cpp include/hexaviewer.hpp)

target_include_directories(test PUBLIC "${PROJECT_SOURCE_DIR}/include")
