cmake_minimum_required(VERSION 3.26)
project(image)

set(CMAKE_CXX_STANDARD 17)
# get cmake file path
file (GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
foreach (file ${files})
    string(REGEX REPLACE "(.+).cpp$" "\\1" exe ${file})
    add_executable (${exe} ${file} BMPFile.cpp)
endforeach ()