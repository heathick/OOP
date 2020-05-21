#pragma once

#include <iostream>
#include <cmath>
#include <iomanip>

template <class T>
struct vertex_t {
    T x;
    T y;
};

template<class T>
std::istream& operator>>(std::istream& is, vertex_t<T>& p) {
    is >> p.x >> p.y;
    return is;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const vertex_t<T>& p) {
    os  << std::fixed << std::setprecision(3) << "[" << p.x << ", " << p.y << "]";
    return os;
}

template<class T>
T calculateDistance(const vertex_t<T>& p1, const vertex_t<T>& p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

template<class T>
T triangleArea(vertex_t<T> p1, vertex_t<T> p2, vertex_t<T> p3) {
    return 0.5 * fabs((p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y 
                - p3.y));
}
