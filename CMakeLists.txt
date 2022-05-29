cmake_minimum_required(VERSION 3.20)
project(Project)

set(CMAKE_CXX_STANDARD 11)

set(PROJECT_HEADERS
        Sudokulib.h
        )
set(PROJECT_SOURCES
        main.cpp
        Sudoku.cpp
        Field.cpp
        )

add_executable(Project ${PROJECT_SOURCES} ${PROJECT_HEADERS})


