cmake_minimum_required(VERSION 3.20)
project(lab_03 C)

set(CMAKE_C_STANDARD 99)

include_directories(inc)

add_executable(lab_03 src/main.c
        src/cdio.c
        src/file_process.c
        src/process.c src/time_analysis.c inc/time_analysis.h)

add_compile_options(-std=c99 -Wall -Werror -pedantic -Wextra -Wfloat-equal -Wfloat-conversion)