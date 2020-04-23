cmake_minimum_required(VERSION 3.9.0)
project(sklearn)

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
