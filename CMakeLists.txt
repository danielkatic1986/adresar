cmake_minimum_required(VERSION 3.29.6)
project(adresar)

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    # Samo na Windows koristiti -static
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

include_directories(
        ${CMAKE_SOURCE_DIR}/deps/windows/PDCurses-3.9
)

link_directories(
        ${CMAKE_SOURCE_DIR}/deps/windows/PDCurses-3.9/wincon
)

add_executable(adresar main.cpp
        Stavka.h
        Adresar.h
        Stavka.cpp
        Adresar.cpp
        Aplikacija.h
        Meni.h
        Meni.cpp
        Aplikacija.cpp
)

target_link_libraries(adresar ${CMAKE_SOURCE_DIR}/deps/windows/PDCurses-3.9/wincon/pdcurses.a)