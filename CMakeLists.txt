cmake_minimum_required(VERSION 3.26)
project(CLion)

set(CMAKE_CXX_STANDARD 17)

# 列出所有源文件
set(SOURCE_FILES
        Tailor.cpp
        ColorReverse.cpp
        Gray.cpp
        ImageScale.cpp
        Brightness.cpp
        # 列出所有其他的 .cpp 文件
)

# 创建可执行文件并关联源文件
add_executable(CLion ${SOURCE_FILES})