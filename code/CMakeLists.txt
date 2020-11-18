cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

project(Reseaux VERSION 1.0)
add_executable(Reseaux tunalloc.c tunalloc.h iftun.c)
