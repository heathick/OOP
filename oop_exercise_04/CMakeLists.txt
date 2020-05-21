cmake_minimum_required(VERSION 3.1)

project(lab4)






add_executable(lab4
    main.cpp
    vertex.hpp
    rhombus.hpp
    pentagon.hpp
    hexagon.hpp)

set_property(TARGET lab3 PROPERTY CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
