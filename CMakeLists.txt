cmake_minimum_required(VERSION 3.9.0)
project(sklearn)

find_package(Eigen3 REQUIRED)
find_package(FDCL_HDF5 REQUIRED)
#add_subdirectory(lib/<lib_dir_name>)

include_directories(
    include
    ${EIGEN3_INCLUDE_DIRS}
    )

add_executable(${PROJECT_NAME}
    main.cpp
    base.h
    KNeighborsClassifier.h
    KNeighborsClassifier.cpp
    RadiusNeighborsClassifier.h
    RadiusNeighborsClassifier.cpp
    )
target_link_libraries(${PROJECT_NAME} fdcl_hdf5)
