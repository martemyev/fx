cmake_minimum_required(VERSION 2.8)


project(fx CXX)


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
      "Choose the type of build: Debug | Release" FORCE)
endif()
string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
message(STATUS "BUILD_TYPE ${BUILD_TYPE}")

add_definitions("-std=c++0x -Wall") # some extra flags


file(GLOB SRC_LIST "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB HDR_LIST "${PROJECT_SOURCE_DIR}/src/*.hpp")
include_directories("${PROJECT_SOURCE_DIR}/src") # for "config.hpp"


configure_file(
  "${PROJECT_SOURCE_DIR}/config.hpp.in"
  "${PROJECT_SOURCE_DIR}/src/config.hpp")


message("\n--------------- configuration information ----------------")
  message("build type     : " ${BUILD_TYPE})
  message("compiler       : " ${CMAKE_CXX_COMPILER})
if(BUILD_TYPE STREQUAL "DEBUG")
  message("compiler flags : " ${CMAKE_CXX_FLAGS_DEBUG})
elseif(BUILD_TYPE STREQUAL "RELWITHDEBINFO")
  message("compiler flags : " ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
elseif(BUILD_TYPE STREQUAL "RELEASE")
  message("compiler flags : " ${CMAKE_CXX_FLAGS_RELEASE})
endif()


add_executable(${PROJECT_NAME} ${SRC_LIST} ${HDR_LIST})

