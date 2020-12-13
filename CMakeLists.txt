cmake_minimum_required(VERSION 3.17)
project(SEPOLIA4)

set(CMAKE_CXX_STANDARD 20)

#========================#
# BOOST library settings #
#========================#

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/mnt/xdata/opt/boost/1.75.0/include")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/mnt/xdata/opt/boost/1.75.0/lib")

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

#======================#
# BLAS/LAPACK settings #
#======================#

FIND_PACKAGE(BLAS REQUIRED)
FIND_PACKAGE(LAPACK REQUIRED)

if(BLAS_FOUND)
    INCLUDE_DIRECTORIES(${BLAS_INCLUDE_DIR})
    LINK_DIRECTORIES(${BLAS_LIBRARIES})
else(BLAS_FOUND)
    MESSAGE(FATAL_ERROR "BLAS NOT FOUND")
endif(BLAS_FOUND)

if(LAPACK_FOUND)
    INCLUDE_DIRECTORIES(${LAPACK_INCLUDE_DIR})
    LINK_DIRECTORIES(${LAPACK_LIBRARIES})
else(LAPACK_FOUND)
    MESSAGE(FATAL_ERROR "LAPACK NOT FOUND")
endif(LAPACK_FOUND)

ADD_EXECUTABLE(SEPOLIA4 main.cpp
        List.cpp
        BoostUblasTests.cpp
        BoostUblasTests.h
        ListTests.cpp
        ListTests.h
        Vector.cpp
        Vector.h
        Matrix.cpp
        Matrix.h)

TARGET_LINK_LIBRARIES(SEPOLIA4 ${LAPACK_LIBRARIES} ${BLAS_LIBARIES})