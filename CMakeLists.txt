cmake_minimum_required(VERSION 3.16)

project(GoodBoy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(MAIN_EXECUTABLE_SRC
    src/executable/main.cpp
)

add_executable(GoodBoy ${MAIN_EXECUTABLE_SRC})
