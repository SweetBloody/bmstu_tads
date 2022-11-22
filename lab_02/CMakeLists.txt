cmake_minimum_required(VERSION 3.20)
project(lab_02 C)

set(CMAKE_C_STANDARD 99)

include_directories(inc)

add_executable(lab_02 src/main.c inc/const.h inc/structs.h
        src/cdio.c inc/cdio.h
        src/file_process.c inc/file_process.h
        src/sorts.c inc/sorts.h
        src/process.c inc/process.h
        src/delete.c inc/delete.h
        src/time_count.c inc/time_count.h)
