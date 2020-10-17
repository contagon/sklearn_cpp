set(tests "test_knn.cpp;test_ms.cpp;test_pipe.cpp;")

set(DEPENDENT_LIBRARIES sklearn Eigen3::Eigen fdcl_hdf5)
set(GMOCK_LIBRARIES gmock gtest gtest_main)


##############################33
# Add and Install Tests
function(add_and_install_tests)
  foreach(source_file ${ARGV})
    message(STATUS "Making ${source_file}")
    get_filename_component(exe_suffix ${source_file} NAME_WE)
    message(STATUS "exe_suffix: ${exe_suffix}")
    string(REGEX REPLACE "_" "-" exe_suffix ${exe_suffix}) # underscore
    set(EXE_NAME ${POD_NAME}_${exe_suffix})

    add_executable(${EXE_NAME} ${source_file})

    # Link GMock
    target_link_libraries(${EXE_NAME} ${GMOCK_LIBRARIES})

    #Link Dependencies
    target_link_libraries(${EXE_NAME} ${DEPENDENT_LIBRARIES})

    target_include_directories(${EXE_NAME} PUBLIC
      $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:include>
      )  
    

    add_test(NAME ${EXE_NAME} COMMAND $<TARGET_FILE:${EXE_NAME}>)

    pods2_install_test(${EXE_NAME})
    # install(TARGETS ${EXE_NAME} EXPORT ${EXE_NAME}
    #   DESTINATION tests)
  endforeach(source_file)
endfunction()

add_and_install_tests(${tests})

  