cmake_minimum_required(VERSION 3.26)
project(CLion)

set(CMAKE_CXX_STANDARD 17)

#list all cpp file
set(SOURCE_FILES
        Tailor.cpp
        ColorReverse.cpp
        Gray.cpp
        ImageScale.cpp
        Chanel.cpp
        Complementary.cpp
        ColorBalance.cpp
        ColorLevel.cpp
)
#set default
set(MAIN_FILE SwapColorSpace.cpp)

add_executable(CLion ${MAIN_FILE})


