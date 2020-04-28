cmake_minimum_required(VERSION 3.10.0)
project(sklearn_cpp)

# Use C++17
# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Load libraries
find_package(Eigen3 REQUIRED)
find_package(FDCL_HDF5 REQUIRED)

# Google Testing
add_subdirectory(${PROJECT_SOURCE_DIR}/extern/googletest/googletest)
ENABLE_TESTING()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Get all header files in 
include_directories(
    include
    ${EIGEN3_INCLUDE_DIRS}
    )

# Get all cpp files into a static library to be shared
file(GLOB SOURCES "src/*.cpp")
add_library(sklearn STATIC ${SOURCES})

# Main executable
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} fdcl_hdf5 sklearn)

# Test executable
file(GLOB TESTS "tests/*.cpp")
add_executable(tests ${TESTS})
target_link_libraries(tests PRIVATE gtest fdcl_hdf5 sklearn)
add_test(NAME tests COMMAND tests
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})