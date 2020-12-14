SET(Boost_USE_STATIC_LIBS OFF)
SET(CMAKE_CXX_STANDARD 20)

#========================#
# BOOST library settings #
#========================#

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/mnt/xdata/opt/boost/1.75.0/include")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/mnt/xdata/opt/boost/1.75.0/lib")

FIND_PACKAGE(Boost REQUIRED COMPONENTS unit_test_framework)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

#=====================#
# Executable settings #
#=====================#

ADD_EXECUTABLE(BOOST_UNIT_TESTS_RUN
        ../List/List.cpp
        ../List/List.h
        ../Matrix/Matrix.cpp
        ../Matrix/Matrix.h
        ../Vector/Vector.cpp
        ../Vector/Vector.h
        ListTests.cpp
        MatrixTests.cpp
        VectorTests.cpp)

TARGET_LINK_LIBRARIES(BOOST_UNIT_TESTS_RUN ${Boost_LIBRARIES})