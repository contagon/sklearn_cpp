#################### BASIC SETUP ####################
cmake_minimum_required(VERSION 3.11)
project(
    sklearn_cpp
    VERSION 0.1
    LANGUAGES CXX)

###############################################################################
#Setup FetchContent and import pods2 files
include(FetchContent)
if(${CMAKE_VERSION} VERSION_LESS 3.14)
  macro(FetchContent_MakeAvailable NAMES)
    foreach(NAME ${NAMES})
      FetchContent_GetProperties(${NAME})
      if(NOT ${NAME}_POPULATED)
        FetchContent_Populate(${NAME})
        add_subdirectory(${${NAME}_SOURCE_DIR} ${${NAME}_BINARY_DIR})
      endif()
    endforeach(NAME)
  endmacro() 
endif()
  
FetchContent_Declare(
  pods2
  GIT_REPOSITORY https://contagon@bitbucket.org/contagon/pods2-public.git
  GIT_TAG origin/clang-tidy
  UPDATE_DISCONNECTED true
  )
FetchContent_MakeAvailable(pods2)

###############################################################################
# Specify the current project as a pod
pods2_initialize_project(${PROJECT_NAME})

###############################################################################
# Import necessary external dependencies

#set(ENABLE_DEPENDENCY_TESTS ON)

FetchContent_Declare(
    Eigen3
    GIT_REPOSITORY  https://contagon@bitbucket.org/contagon/eigen3-new-pod2.git
    GIT_TAG         master
)
FetchContent_MakeAvailable(Eigen3)

#package for reading/writing h5 files
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(FDCL_HDF5 REQUIRED)

###############################################################################
# Add subdirectories to src/exe files
pods2_add_src_directory(src)
#pods2_add_exe_directory(exe)

###############################################################################
# Setup testing
pods2_add_test_directory(tests)

###############################################################################
# Configure install 
pods2_install_project_includes()
pods2_install_project_targets()

#################### Make main executable ####################
add_executable(main_test main.cpp)
target_link_libraries(main_test PRIVATE sklearn fdcl_hdf5)
