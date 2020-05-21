#include <iostream>
#include <algorithm>

#include "stack.hpp"
#include "rhombus.hpp"

int main() {
    cntrs::stack_t<Rhombus<double>> s;
    int command, pos;
    std::cout << "1 - add element to stack(push/insert by iterator)" << std::endl;
    std::cout << "2 - delete element from stack(pop/erase by index/erase by iterator)" << std::endl;
    std::cout << "3 - range-based for print" << std::endl;
    std::cout << "4 - count_if example" << std::endl;
    std::cout << "5 - top element" << std::endl;
    std::cin >> command;
    while(true) {
        if(command == 0) {
            break;
        } else if(command == 1) {
            std::cout << "Enter coordinates" << std::endl;
            vertex_t<double> v1, v2, v3, v4;
            std::cin >> v1 >> v2 >> v3 >> v4;
            try {
                Rhombus<double> r{v1, v2, v3, v4};
            } catch(std::exception& e) {
                std::cout << e.what() << std::endl;
                std::cin >> command;
                continue;
            }
            Rhombus<double> r{v1, v2, v3, v4};
            std::cout << "1 - push to stack" << std::endl;
            std::cout << "2 - insert by iterator" << std::endl;
            std::cin >> command;
            if(command == 1) {
                s.push(r);
            } else if(command == 2) {
                std::cout << "Enter index" << std::endl;
                std::cin >> pos;
                s.insert(pos, r);
            } else {
                std::cout << "Wrong command" << std::endl;
                std::cin >> command;
                continue;
            }
        } else if(command == 2) {
            std::cout << "1 - pop" << std::endl;
            std::cout << "2 - erase by index" << std::endl;
            std::cout << "3 - erase by iterator" << std::endl;
            std::cin >> command;
            if(command == 1) {
                s.pop();
            } else if(command == 2) {
                std::cout << "Enter index" << std::endl;
                std::cin >> pos;
                s.erase(pos);
            } else if(command == 3) {
                std::cout << "Enter index" << std::endl;
                std::cin >> pos;
                auto temp = s.begin();
                for(int i = 0; i < pos; ++i) {
                    ++temp;
                }
                s.erase(temp);
            } else {
                std::cout << "Wrong command" << std::endl;
                std::cin >> command;
                continue;
            }
        } else if(command == 3) {
            for(const auto& item : s) {
                item.print(std::cout);
            }
        } else if(command == 4) {
            std::cout << "Enter required square" << std::endl;
            std::cin >> pos;
            std::cout << "Number of rhombes with area less than " << pos << " equals ";
            std::cout << std::count_if(s.begin(), s.end(), [pos](Rhombus<double> r) {return r.area() < pos;}) << std::endl;
        } else if(command == 5) {
            try {
                s.top();
            } catch(std::exception& e) {
                std::cout << e.what() << std::endl;
                std::cin >> command;
                continue;
            }
            Rhombus temp = s.top();
            std::cout << "Top: ";
            temp.print(std::cout);
        } else {
            std::cout << "Wrong command" << std::endl;
        }
        std::cin >> command;
    }
    return 0;
}

