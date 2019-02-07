cmake_minimum_required(VERSION 3.0)
project(random)

set(CMAKE_CXX_STANDARD 11)

option(RANDOM_TEST_BUILD_ENABLE_FLAG "Enable test" ON) # enable test

include(pkg.dep.cmake)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(RANDOM_LIB_NAME ${PROJECT_NAME})
set(RANDOM_UINT_TEST_NAME "${PROJECT_NAME}-unit-tests")

add_subdirectory(src)

################################
## test configure
################################
if (RANDOM_TEST_BUILD_ENABLE_FLAG)
    MESSAGE(STATUS "TEST is enabled")
    enable_testing()
    add_subdirectory(tests)
endif ()
