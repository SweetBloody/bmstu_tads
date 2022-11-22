cmake_minimum_required(VERSION 3.20)
project(lab_04 C)

set(CMAKE_C_STANDARD 99)

include_directories(inc)

add_executable(lab_04 src/main.c
        src/cdio.c
        src/process.c src/analysis.c inc/analysis.h)
