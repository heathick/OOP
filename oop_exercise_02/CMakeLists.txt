cmake_minimum_required(VERSION 3.1)

project(lab2)

add_executable(lab2
    main.cpp
    modulo.cpp
)

set_property(TARGET lab1 PROPERTY CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")