cmake_minimum_required(VERSION 4.0)
project(Rev_tree C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Rev_tree
        revision.c
        revision.h
        main.c
)
