cmake_minimum_required(VERSION 3.10.0)
project(sklearn)

# Use C++17
# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Load libraries
find_package(Eigen3 REQUIRED)
find_package(FDCL_HDF5 REQUIRED)
#add_subdirectory(lib/<lib_dir_name>)

# Get all header files in 
include_directories(
    include
    ${EIGEN3_INCLUDE_DIRS}
    )

# Get all cpp files
file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME}
    ${SOURCES}
    )

target_link_libraries(${PROJECT_NAME} fdcl_hdf5)
