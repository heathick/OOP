#include <iostream>
#include <vector>

#include "point.hpp"
#include "figure.hpp"
#include "rhombus.hpp"
#include "pentagon.hpp"
#include "hexagon.hpp"

int get_command() {
    int command;
    std::cin >> command;
    return command;
}

int main() {
    int command1, command2;
    std::vector<Figure*> figures;
    std::cout << "1 - add figure to the vector\n"
                 "2 - delete figure from the vector\n"
                 "3 - call common functions for the whole vector\n"
                 "4 - get total area of figures in vector\n"
                 "0 - exit\n";
    while((command1 = get_command()) != 0) {
        if(command1 == 1) {
            Figure* f;
            std::cout << "1 - Rhombus, 2 - Pentagon, 3 - Hexagon" << std::endl;
            std::cin >> command2;
            try {
                if(command2 == 1) {
                    f = new Rhombus(std::cin);
                } else if(command2 == 2) {
                    f = new Pentagon{std::cin};
                } else if(command2 == 3) {
                    f = new Hexagon{std::cin};
                } else {
                    std::cout << "Wrong input" << std::endl;
                }
                figures.push_back(f);
            } catch(std::exception& e) {
                std::cerr << e.what() << std::endl;
            }    
        } else if(command1 == 2) {
            std::cout << "Enter index" << std::endl;
            std::cin >> command2;
            if(command2 < static_cast<int>(figures.size())) {
                delete figures[command2];
                figures.erase(figures.begin() + command2);
            } else {
                std::cout << "Element with such index doesn't exist" << std::endl;
            }
        } else if(command1 == 3) {
            for(const auto& figure : figures) {
                figure->Print(std::cout);
                std::cout << figure->Center() << std::endl;
                std::cout << figure->Square() << std::endl;
            }
        } else if(command1 == 4) {
            double result = 0;
            for(const auto& figure : figures) {
                result += figure->Square();
            }
            std::cout << result << std::endl;
        } else if(command1 == 5) {
            break;
        } else {
            std::cout << "Wrong command" << std::endl;
        }
    } 
    for(const auto& f : figures) {
        delete f;
    }
    return 0;
}
