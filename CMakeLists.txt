cmake_minimum_required(VERSION 3.12)
project(image)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)
add_library(BMPLib_Shared SHARED MyLib/BMPFile.cpp)
#target_include_directories(BMP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
foreach(file ${files})
    string(REGEX REPLACE "(.+).cpp$" "\\1" exe ${file})
    add_executable(${exe} ${file})
    target_link_libraries(${exe} BMPLib_Shared)

endforeach()
