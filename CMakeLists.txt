cmake_minimum_required(VERSION 3.31)
project(adresar)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(adresar main.cpp
        Stavka.h
        Adresar.h
        Stavka.cpp
)
