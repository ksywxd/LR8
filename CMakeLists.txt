cmake_minimum_required(VERSION 4.0)
project(LR8)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Task_1)

if(MSVC)
    add_compile_options(/utf-8)
else()
    add_compile_options("-finput-charset=UTF-8" "-fexec-charset=UTF-8")
endif()
