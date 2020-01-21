set(HEADER_FILES
        xoshiro_gen.h
        xoshiro.h
        )

set(SOURCE_FILES
        xoshiro.cpp
        )

# set binary path and lib storage path for compiling process.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


# make lib.
add_library(${RANDOM_LIB_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(
        ${RANDOM_LIB_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)


# lib alias to makes it possible to always use the namespace version consistently
add_library(xoshiro::${RANDOM_LIB_NAME} ALIAS ${RANDOM_LIB_NAME})

set(TARGETS_EXPORT_NAME ${RANDOM_LIB_NAME}-targets)
set(RANDOM_CMAKE_DIR lib/cmake/xoshiro)


##########################
##### install files
##########################
# install bin and libs.
install(TARGETS ${RANDOM_LIB_NAME}
        EXPORT ${TARGETS_EXPORT_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )

# install header.
install(DIRECTORY "./"
        DESTINATION "include"
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp"
        )

# install export target and config for find_package
install(EXPORT ${TARGETS_EXPORT_NAME} DESTINATION ${RANDOM_CMAKE_DIR} NAMESPACE xoshiro::)
include(CMakePackageConfigHelpers)
configure_package_config_file(
        "xoshiro-config.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/xoshiro-config.cmake"
        INSTALL_DESTINATION ${RANDOM_CMAKE_DIR}
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/xoshiro-config.cmake" DESTINATION ${RANDOM_CMAKE_DIR})
