#################### BASIC SETUP ####################
cmake_minimum_required(VERSION 3.15.0)
project(
    sklearn_cpp
    VERSION 0.1
    LANGUAGES CXX)

include(FetchContent)


#################### Load libraries ####################
#eigen 3
FetchContent_Declare(
    Eigen3
    GIT_REPOSITORY  https://gitlab.com/libeigen/eigen.git
    GIT_TAG         master
)
FetchContent_MakeAvailable(Eigen3)

#package for reading/writing h5 files
find_package(FDCL_HDF5 REQUIRED)

#google testing
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.8.0
)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()


#################### Make Sklearn library ####################
add_library(sklearn 
                src/model_selection.cpp
                src/KNeighborsClassifier.cpp
                src/MinMaxScaler.cpp
                src/PCA.cpp
                src/Pipeline.cpp
                src/RadiusNeighborsClassifier.cpp
                src/StandardScaler.cpp
                include/model_selection.h
                include/KNeighborsClassifier.h
                include/MinMaxScaler.h
                include/PCA.h
                include/Pipeline.h
                include/RadiusNeighborsClassifier.h
                include/StandardScaler.h
                include/base.h)
target_include_directories(sklearn PUBLIC include)

target_link_libraries(sklearn PUBLIC Eigen3::Eigen)
target_compile_features(sklearn PUBLIC cxx_std_17)


#################### Make main executable ####################
add_executable(main_test main.cpp)
target_link_libraries(main_test PRIVATE sklearn fdcl_hdf5)


#################### Add Tests in ####################
add_executable(tests
                tests/test_all.cpp
                tests/test_knn.cpp
                tests/test_ms.cpp
                tests/test_pipe.cpp)
target_link_libraries(tests PRIVATE gtest fdcl_hdf5 sklearn)
add_custom_target(test COMMAND tests)