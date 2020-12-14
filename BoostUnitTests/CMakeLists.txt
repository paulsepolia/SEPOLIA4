SET(Boost_USE_STATIC_LIBS OFF)
SET(CMAKE_CXX_STANDARD 20)

#========================#
# BOOST library settings #
#========================#

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/mnt/xdata/opt/boost/1.75.0/include")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/mnt/xdata/opt/boost/1.75.0/lib")

FIND_PACKAGE(Boost REQUIRED COMPONENTS unit_test_framework)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

ADD_EXECUTABLE(BOOST_UNIT_TESTS_RUN
        ../Vector/Vector.cpp
        ../Vector/Vector.h
        ../Matrix/Matrix.cpp
        ../Matrix/Matrix.h
        VectorTests.cpp
        MatrixTests.cpp)

TARGET_LINK_LIBRARIES(BOOST_UNIT_TESTS_RUN ${Boost_LIBRARIES})