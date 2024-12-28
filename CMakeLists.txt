cmake_minimum_required(VERSION 3.15)

project(MenuMaker)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

add_executable(MenuMaker
    main.cpp
    menu.h
)
