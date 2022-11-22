cmake_minimum_required(VERSION 3.20)
project(lab_05 C)

set(CMAKE_C_STANDARD 99)

include_directories(inc)

add_executable(lab_05 src/main.c
        src/cdio.c inc/cdio.h src/list.c src/array.c inc/array.h src/process.c inc/process.h src/analysis.c inc/analysis.h)
