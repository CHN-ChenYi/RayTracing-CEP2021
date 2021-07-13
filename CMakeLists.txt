CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
INCLUDE("${CMAKE_SOURCE_DIR}/third_party/CSL/csl-base.cmk")
INCLUDE("${CMAKE_SOURCE_DIR}/third_party/CSL/csl-main.cmk")
INCLUDE("${CMAKE_SOURCE_DIR}/third_party/fltk/fltk.cmk")

PROJECT(RayTracing)

ADD_DEFINITIONS(${STRING_CXX_FLAGS})

SET_CSL_PATH("${CMAKE_SOURCE_DIR}/third_party/CSL/")
SET_FLTK_PATH("${CMAKE_SOURCE_DIR}/third_party/fltk/")

#directories

ADD_SUBDIRECTORY(src src)
