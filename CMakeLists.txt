cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(myprogram 
    main.cpp
    src/EightQueens/EightQueens.cpp
)

target_include_directories(myprogram PRIVATE include)