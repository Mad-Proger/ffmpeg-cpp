cmake_minimum_required(VERSION 3.24)
include(FindPkgConfig)

project(FFmpeg-cpp)

set(HEADER_DIR "${PROJECT_SOURCE_DIR}/include")

add_subdirectory(src/avcodec)
