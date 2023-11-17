cmake_minimum_required(VERSION 3.5)

project(RentItNowTest LANGUAGES CXX)

enable_testing()

find_package(Threads REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

if ($ENV{GOOGLETEST_DIR})
    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else()
    if (NOT "${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/googletest-1.14.0" STREQUAL "")
        message(WARNING "Using googletest src dir specified at Qt Creator wizard")
    endif()
    set(GOOGLETEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/googletest-1.14.0")
endif()

if (EXISTS ${GOOGLETEST_DIR})
    set(GTestSrc ${GOOGLETEST_DIR}/googletest)
    set(GMockSrc ${GOOGLETEST_DIR}/googlemock)
elseif (UNIX AND EXISTS /usr/src/gtest)
    set(GTestSrc /usr/src/gtest)
    message(WARNING "Using gtest from system")
    if (EXISTS /usr/src/gmock)
        set(GMockSrc /usr/src/gmock)
    endif()
else()
    message(FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif()
# Include directories for your application
# Set the source files for your application
set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)
if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
endif()

include_directories(${GTestIncludes} ${CMAKE_CURRENT_SOURCE_DIR}/../src/)


add_executable(RentItNowTest main.cpp car_test.cpp ${GTestFiles}
    car_manager_test.cpp
    car_repo_test.cpp
    car_manager_test.h
    user_repo_test.cpp)

file(GLOB MODEL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../src/model/*.cpp)
target_sources(RentItNowTest PRIVATE ${MODEL_SOURCES})
file(GLOB SERVICE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../src/service/*.cpp)
target_sources(RentItNowTest PRIVATE ${SERVICE_SOURCES})
file(GLOB REPOSITORY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../src/repository/*.cpp)
target_sources(RentItNowTest PRIVATE ${REPOSITORY_SOURCES})
target_link_libraries(RentItNowTest PRIVATE Qt${QT_VERSION_MAJOR}::Core)

add_test(NAME RentItNowTest COMMAND RentItNowTest)
target_link_libraries(RentItNowTest PRIVATE Threads::Threads)

