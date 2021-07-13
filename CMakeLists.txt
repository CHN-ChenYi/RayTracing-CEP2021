CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
INCLUDE("${CMAKE_SOURCE_DIR}/third_party/CSL/csl-base.cmk")
INCLUDE("${CMAKE_SOURCE_DIR}/third_party/CSL/csl-main.cmk")
INCLUDE("${CMAKE_SOURCE_DIR}/third_party/fltk/fltk.cmk")
INCLUDE("${CMAKE_SOURCE_DIR}/third_party/stduuid/stduuid.cmk")

PROJECT(RayTracing)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

ADD_DEFINITIONS(${STRING_CXX_FLAGS})

SET_CSL_PATH("${CMAKE_SOURCE_DIR}/third_party/CSL/")
SET_FLTK_PATH("${CMAKE_SOURCE_DIR}/third_party/fltk/")
SET_STDUUID_PATH("${CMAKE_SOURCE_DIR}/third_party/stduuid/")

#directories

ADD_SUBDIRECTORY(src src)
