cmake_minimum_required(VERSION 3.15.0)
project(
    sklearn_cpp
    VERSION 0.1
    LANGUAGES CXX)

include(FetchContent)

# Load libraries
FetchContent_Declare(
    Eigen3
    GIT_REPOSITORY  https://gitlab.com/libeigen/eigen.git
    GIT_TAG         master
)
FetchContent_MakeAvailable(Eigen3)

FetchContent_Declare(
    fdcl_hdf5
    GIT_REPOSITORY  https://github.com/skulumani/fdcl-hdf5.git
    GIT_TAG         master
)
FetchContent_MakeAvailable(fdcl_hdf5)


## Make Sklearn library
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


## Make main executable
add_executable(main_test main.cpp)
target_link_libraries(main_test PRIVATE Eigen3::Eigen sklearn fdcl_hdf5)