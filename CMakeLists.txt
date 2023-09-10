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
)
#set default
set(MAIN_FILE Chanel.cpp)

add_executable(CLion ${MAIN_FILE})


