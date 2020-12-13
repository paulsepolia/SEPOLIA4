cmake_minimum_required(VERSION 3.17)
project(SEPOLIA4)

set(CMAKE_CXX_STANDARD 20)

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/mnt/xdata/opt/boost/1.75.0/include")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/mnt/xdata/opt/boost/1.75.0/lib")

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

add_executable(SEPOLIA4 main.cpp List.cpp)