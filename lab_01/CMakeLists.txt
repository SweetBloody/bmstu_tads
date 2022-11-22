cmake_minimum_required(VERSION 3.20)
project(lab_01 C)

set(CMAKE_C_STANDARD 99)

include_directories(inc)

add_executable(lab_01 src/main.c
        src/cdio.c
        src/norm_func.c
        src/process.c)
