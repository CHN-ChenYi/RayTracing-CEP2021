﻿CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
INCLUDE("${CMAKE_SOURCE_DIR}/third_party/CSL/csl-base.cmk")
INCLUDE("${CMAKE_SOURCE_DIR}/third_party/CSL/csl-main.cmk")
INCLUDE("${CMAKE_SOURCE_DIR}/third_party/fltk/fltk.cmk")
INCLUDE("${CMAKE_SOURCE_DIR}/third_party/stduuid/stduuid.cmk")

PROJECT(RayTracing)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lpthread -fopenmp /execution-charset:utf-8")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

ADD_DEFINITIONS(${STRING_CXX_FLAGS})

SET_CSL_PATH("${CMAKE_SOURCE_DIR}/third_party/CSL/")
SET_FLTK_PATH("${CMAKE_SOURCE_DIR}/third_party/fltk/")
SET_STDUUID_PATH("${CMAKE_SOURCE_DIR}/third_party/stduuid/")

#directories

ADD_SUBDIRECTORY(src src)
