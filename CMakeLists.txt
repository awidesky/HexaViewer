cmake_minimum_required(VERSION 3.10)

project(HexaViewer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test src/test.cpp include/hexaviewer.hpp)
add_executable(test_fast src/test_fast.cpp include/hexaviewer_fast.hpp)
add_executable(test_comp src/test_comp.cpp include/hexaviewer.hpp include/hexaviewer_fast.hpp)

target_include_directories(test PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(test_fast PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(test_comp PUBLIC "${PROJECT_SOURCE_DIR}/include")
