cmake_minimum_required(VERSION 3.11)

# find all source and header files
set(SRCS Pipeline.cpp
          PCA.cpp
          model_selection.cpp
          KNeighborsClassifier.cpp
          MinMaxScaler.cpp
          RadiusNeighborsClassifier.cpp
          StandardScaler.cpp)
# set(SRCS Pipeline.cpp PCA.cpp)

#create library
set(LIB_NAME sklearn)
pods2_add_library(${LIB_NAME} "${SRCS}") 

# Set Library Properties
target_include_directories(${LIB_NAME} PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  )  
target_compile_features(${LIB_NAME} PUBLIC cxx_std_17)
target_link_libraries(${LIB_NAME} PUBLIC Eigen3::Eigen)
  
# Install Library
pods2_install_library(${LIB_NAME})