cmake_minimum_required(VERSION 3.31)
project(dry)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(dry
        main.cpp
        Pirate.cpp
        Pirate.h)
