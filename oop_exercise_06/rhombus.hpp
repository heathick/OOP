#pragma once

#include <array>

#include "vertex.hpp"

template<class T>
double checkIfRhombus(const vertex_t<T> p1, const vertex_t<T>& p2,
        const vertex_t<T>& p3, const vertex_t<T>& p4) {
    T d1 = calculateDistance(p1, p2);
    T d2 = calculateDistance(p1, p3);
    T d3 = calculateDistance(p1, p4);
    if(d1 == d2) {
        return d3;
    } else if(d1 == d3) {
        return d2;
    } else if(d2 == d3) {
        return d1;
    } else {
        throw std::invalid_argument("Entered coordinates are not forming Rhombus. Try entering new coordinates");
    }
}

template <class T>
struct Rhombus {
    std::array<vertex_t<T>, 4> points;
    T smallerDiagonal, biggerDiagonal;
    Rhombus(const vertex_t<T>& p1, const vertex_t<T>& p2, const vertex_t<T>& p3,
            const vertex_t<T>& p4);
    double area() const;
    vertex_t<T> center() const;
    void print(std::ostream& os) const;
};

template<class T>
Rhombus<T>::Rhombus(const vertex_t<T>& p1, const vertex_t<T>& p2,
        const vertex_t<T>& p3, const vertex_t<T>& p4) {
    try {
        T d1 = checkIfRhombus(p1, p2, p3, p4);
        T d2 = checkIfRhombus(p2, p1, p3, p4);
        T d3 = checkIfRhombus(p3, p1, p2, p4);
        T d4 = checkIfRhombus(p4, p1, p2, p3);
        if(d1 == d2 || d1 == d4) {
            if(d1 < d3) {
                smallerDiagonal = d1;
                biggerDiagonal = d3;
            } else {
                smallerDiagonal = d3;
                biggerDiagonal = d1;
            }
        } else if(d1 == d3) {
            if(d1 < d2) {
                smallerDiagonal = d1;
                biggerDiagonal = d2;
            } else {
                smallerDiagonal = d2;
                biggerDiagonal = d1;
            }
        }
    } catch(std::exception& e) {
        throw std::invalid_argument(e.what());
        return;
    }
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
}

template<class T>
double Rhombus<T>::area() const {
    return smallerDiagonal * biggerDiagonal / 2.0;
}

template<class T>
vertex_t<T> Rhombus<T>::center() const {
    if(calculateDistance(points[0], points[1]) == smallerDiagonal || 
            calculateDistance(points[0], points[1]) == biggerDiagonal) {
        return {((points[0].x + points[1].x) / 2.0), ((points[0].y + points[1].y) / 2.0)};
    } else if(calculateDistance(points[0], points[2]) == smallerDiagonal || 
            calculateDistance(points[0], points[2]) == biggerDiagonal) {
        return {((points[0].x + points[2].x) / 2.0), ((points[0].y + points[2].y) / 2.0)};
    } else {    
        return {((points[0].x + points[3].x) / 2.0), ((points[0].y + points[3].y) / 2.0)};
    }
}

template<class T>
void Rhombus<T>::print(std::ostream& os) const {
    os << "Rhombus: ";
    for(const auto& p : points) {
        os << p << ' ';
    }
    os << std::endl;
}
