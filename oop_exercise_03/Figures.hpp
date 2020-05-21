#pragma once

#include <iostream>
#include <vector>

struct Point {
    double x, y;
};

double calculateDistance(const Point& lhs, const Point& rhs);
bool operator<(const Point& lhs, const Point& rhs);
std::istream& operator>>(std::istream& is, Point& p);
std::ostream& operator<<(std::ostream& os, const Point& p);
std::ostream& operator<<(std::ostream& os, const std::vector<Point> v);

class Figure {
public:
    virtual Point Center() const = 0;
    virtual double Square() const = 0;
    virtual void Print(std::ostream& os) const = 0;
    virtual ~Figure() = default;
};

class Rhombus : public Figure {
public:
    Rhombus(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
    Point Center() const override;
    double Square() const override;
    void Print(std::ostream& os) const override;
private:
    std::vector<Point> points;
    double smallerDiagonal, biggerDiagonal;
};

class Pentagon : public Figure {
public:
    Pentagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5);
    Point Center() const override;
    double Square() const override;
    void Print(std::ostream& os) const override;
private:
    std::vector<Point> points;
};

class Hexagon : public Figure {
public:
    Hexagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5, const Point& p6);
    Point Center() const override;
    double Square() const override;
    void Print(std::ostream& os) const override;
private:
    std::vector<Point> points;
};

