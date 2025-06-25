cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
find_package(Boost REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread system)

add_executable(mythreads
    main.cpp
    src/Threads/Threads.cpp
    src/Threads/Threads2.cpp
    src/Threads/Threads3.cpp
    src/Threads/Threads_datarace.cpp
    src/Threads/Challenge_1.cpp
    src/Threads/Challenge_2.cpp
    src/Threads/Challenge_3.cpp
)

target_include_directories(mythreads PRIVATE include)

target_include_directories(mythreads PRIVATE ${CURL_INCLUDE_DIRS})

target_link_libraries(mythreads PRIVATE CURL::libcurl)
target_link_libraries(mythreads PRIVATE Boost::boost)
target_link_libraries(mythreads PRIVATE Boost::thread Boost::system pthread)