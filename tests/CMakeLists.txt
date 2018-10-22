cmake_minimum_required(VERSION 3.10)

set(COVERAGE OFF CACHE BOOL "Coverage")


find_path(CSM_INCLUDE_DIR NAMES "csm.h"
            PATH_SUFFIXES "csm"
            PATHS $ENV{CONDA_PREFIX}/include/)
find_library(CSM_LIBRARY csmapi PATHS $ENV{CONDA_PREFIX}/lib)


# Link runSensorUtilsTests with what we want to test and the GTest and pthread library

add_executable(runSensorUtilsTests TestMain.cpp
                                   SensorCoreTesting.cpp
                                   SensorMathTesting.cpp
                                   SensorModelTesting.cpp
                                   ShapeModelTesting.cpp
                                   ${CMAKE_CURRENT_LIST_DIR}/csm_fixture/model.cpp
                                   ${CMAKE_CURRENT_LIST_DIR}/csm_fixture/plugin.cpp
)

target_link_libraries(runSensorUtilsTests PUBLIC
                      sensorutils
                      ${GMOCK_LIBRARY}
                      pthread
                      ${CMAKE_DL_LIBS}
                      ${CSM_LIBRARY})

include_directories(${SENSORUTILS_PRIVATE_INCLUDE_DIRS}
                    ${SENSORUTILS_PUBLIC_INCLUDE_DIRS}
                    ${ARMADILLO_INCLUDE_DIR}
                    ${CSM_INCLUDE_DIR})

if(COVERAGE)
    target_link_libraries(runSensorUtilsTests PRIVATE --coverage)
endif()

gtest_discover_tests(runSensorUtilsTests WORKING_DIRECTORY tests)
