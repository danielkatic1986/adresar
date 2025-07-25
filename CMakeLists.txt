cmake_minimum_required(VERSION 3.29.6)
project(adresar)

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    # Samo na Windows koristiti -static
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
    include_directories(${CMAKE_SOURCE_DIR}/deps/windows/PDCurses-3.9)
    link_directories(${CMAKE_SOURCE_DIR}/deps/windows/PDCurses-3.9/wincon)
    set(CURSES_LIB ${CMAKE_SOURCE_DIR}/deps/windows/PDCurses-3.9/wincon/pdcurses.a)
else()
    # Na Macu i Linuxu koristi ncurses
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
    set(CURSES_LIB ${CURSES_LIBRARIES})
endif()

add_executable(adresar
        main.cpp
        Stavka.h
        Adresar.h
        Stavka.cpp
        Adresar.cpp
        Aplikacija.h
        Meni.h
        Meni.cpp
        Aplikacija.cpp
)

target_link_libraries(adresar ${CURSES_LIB})