cmake_minimum_required(VERSION 3.1)

project(lab3)

enable_testing()

set(Figures_source Figures.cpp)

add_library(figures STATIC ${Figures_source})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(testFigures test.cpp)
target_link_libraries(testFigures ${Boost_LIBRARIES} figures)
add_test(NAME Test1 COMMAND test1)

add_executable(lab3
    main.cpp
    point.cpp
    rhombus.cpp
    pentagon.cpp
    hexagon.cpp)

set_property(TARGET lab3 PROPERTY CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
