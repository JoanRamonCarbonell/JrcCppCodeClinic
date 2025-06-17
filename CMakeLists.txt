cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(mythreads
    main.cpp
    src/Threads/Threads.cpp
    src/Threads/Threads2.cpp
    src/Threads/Threads3.cpp
    src/Threads/Threads_datarace.cpp
    src/Threads/Challenge_1.cpp
    src/Threads/Challenge_2.cpp
)

target_include_directories(mythreads PRIVATE include)