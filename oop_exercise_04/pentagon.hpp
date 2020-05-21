#pragma once

#include <array>
#include <cmath>

#include "vertex.hpp"

template <class T>
struct Pentagon {
    std::array<vertex_t<T>, 5> points;
    Pentagon(const vertex_t<T>& p1, const vertex_t<T>& p2, const vertex_t<T>& p3,
            const vertex_t<T>& p4, const vertex_t<T>& p5);
    double area() const;
    vertex_t<T> center() const;
    void print(std::ostream& os) const;
};

template <class T>
Pentagon<T>::Pentagon(const vertex_t<T>& p1, const vertex_t<T>& p2,
        const vertex_t<T>& p3, const vertex_t<T>& p4, const vertex_t<T>& p5) {
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
    points[4] = p5;
}

template <class T>
double Pentagon<T>::area() const {
    double result = 0;
    for(unsigned i = 0; i < points.size(); ++i) {
        vertex_t p1 = i ? points[i - 1] : points[points.size() - 1];
        vertex_t p2 = points[i];
        result += (p1.x - p2.x) * (p1.y + p2.y);
    }
    return fabs(result) / 2.0;
}

template <class T>
vertex_t<T> Pentagon<T>::center() const {
    T x = 0;
    T y = 0;
    for(const auto& p : points) {
        x += p.x;
        y += p.y;
    }
    x /= points.size();
    y /= points.size();
    return {x, y};
}

template <class T>
void Pentagon<T>::print(std::ostream& os) const {
    os << "Pentagon: ";
    for(const auto& p : points) {
        os << p << ' ';
    }
    os << std::endl;
}
