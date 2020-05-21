#include <iostream>

#include "vertex.hpp"
#include "templates.hpp"
#include "rhombus.hpp"
#include "pentagon.hpp"
#include "hexagon.hpp"

int main() {
    int command;
    std::cout << "1 - Rhombus" << std::endl;
    std::cout << "2 - Pentagon" << std::endl;
    std::cout << "3 - Hexagon" << std::endl;
    std::cout << "0 - Exit" << std::endl;
    std::cin >> command;
    while(command != 0) {
        if(command == 1) {
            vertex_t<double> p1, p2, p3, p4;
            std::cin >> p1 >> p2 >> p3 >> p4;
            try {
                Rhombus r{p1, p2, p3, p4};
            } catch(std::exception& e) {
                std::cout << e.what() << std::endl;
                std::cin >> command;
                continue;
            }
            Rhombus r{p1, p2, p3, p4};
            print(r, std::cout);
            std::cout << area(r) << std::endl;
            std::cout << center(r) << std::endl;
            std::tuple<vertex_t<double>, vertex_t<double>, vertex_t<double>, 
                vertex_t<double>> r1{p1, p2, p3, p4};
            std::cout << "Rhombus: ";
            print(r1, std::cout);
            std::cout << area(r1) << std::endl;
            std::cout << center(r1) << std::endl;
        } else if(command == 2) {
            vertex_t<double> p1, p2, p3, p4, p5;
            std::cin >> p1 >> p2 >> p3 >> p4 >> p5;
            Pentagon r{p1, p2, p3, p4, p5};
            print(r, std::cout);
            std::cout << area(r) << std::endl;
            std::cout << center(r) << std::endl;
            std::tuple<vertex_t<double>, vertex_t<double>, vertex_t<double>, 
                vertex_t<double>, vertex_t<double>> r1{p1, p2, p3, p4, p5};
            std::cout << "Pentagon: ";
            print(r1, std::cout);
            std::cout << area(r1) << std::endl;
            std::cout << center(r1) << std::endl;
        } else if(command == 3) {
            vertex_t<double> p1, p2, p3, p4, p5, p6;
            std::cin >> p1 >> p2 >> p3 >> p4 >> p5 >> p6;
            Hexagon r{p1, p2, p3, p4, p5, p6};
            print(r, std::cout);
            std::cout << area(r) << std::endl;
            std::cout << center(r) << std::endl;
            std::tuple<vertex_t<double>, vertex_t<double>, vertex_t<double>, 
                vertex_t<double>, vertex_t<double>, vertex_t<double>> 
                    r1{p1, p2, p3, p4, p5, p6};
            std::cout << "Hexagon: ";
            print(r1, std::cout);
            std::cout << area(r1) << std::endl;
            std::cout << center(r1) << std::endl; 
        } else {
            std::cout << "Wrong command" << std::endl; 
        }
        std::cin >> command;
    }
}
