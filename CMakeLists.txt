cmake_minimum_required(VERSION 3.21)
project(GPXStats)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(GPXStats main.cpp GPXData.cpp GPXList.cpp)

include(FindPkgConfig)
find_package(Tinyxml2 REQUIRED)
include_directories(${TINYXML2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${TINYXML2_LIBRARY})
