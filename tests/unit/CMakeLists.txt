
set(TEST_SOURCE_FILES
        oshinro_random_test.cpp
        )

# set binary path and lib storage path wile compiling process.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_executable(${RANDOM_UINT_TEST_NAME} ${TEST_SOURCE_FILES})


# Extra linking for the project.
target_link_libraries(${RANDOM_UINT_TEST_NAME}
        PRIVATE GTest::gtest GTest::gtest_main ${RANDOM_LIB_NAME} ${RANDOM_EXTRA_LIBS}
        )

add_test(NAME ${RANDOM_UINT_TEST_NAME} COMMAND ${RANDOM_UINT_TEST_NAME})

##########################
##### install binary files
##########################
install(TARGETS ${RANDOM_UINT_TEST_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )
