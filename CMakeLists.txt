cmake_minimum_required(VERSION 3.29.6)
project(adresar)

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    # Samo na Windows koristiti -static
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

add_executable(adresar main.cpp
        Stavka.h
        Adresar.h
        Stavka.cpp
        Adresar.cpp
)
