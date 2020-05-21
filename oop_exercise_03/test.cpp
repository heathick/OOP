#include "Figures.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testFigures

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(testRhombusSqaure) {
    Point p1{-2, 0};
    Point p2{0, 2};
    Point p3{2, 0};
    Point p4{0, -2};
    Rhombus r{p1,p2,p3,p4};
    BOOST_CHECK_EQUAL(r.Square(), 8);
    p2.y = 1;
    p4.y = -1;
    Rhombus r1{p1,p2,p3,p4};
    BOOST_CHECK_EQUAL(r1.Square(), 4);
}

BOOST_AUTO_TEST_CASE(testRhombusCenter) {
    Point p1{-2, 0};
    Point p2{0, 2};
    Point p3{2, 0};
    Point p4{0, -2};
    Rhombus r{p1,p2,p3,p4};
    BOOST_CHECK_EQUAL(r.Center().x, 0);
    BOOST_CHECK_EQUAL(r.Center().y, 0);
    p2.y = 1;
    p4.y = -1;
    Rhombus r1{p1,p2,p3,p4};
    BOOST_CHECK_EQUAL(r1.Center().x, 0);
    BOOST_CHECK_EQUAL(r1.Center().y, 0);   
}

BOOST_AUTO_TEST_CASE(testPentagonSquare) {
    Point p1{-2, 0};
    Point p2{0, 2};
    Point p3{2, 0};
    Point p4{3, 0};
    Point p5{0, -2};
    Pentagon p{p1, p2, p3, p4, p5};
    BOOST_CHECK_EQUAL(p.Square(), 9);
}

BOOST_AUTO_TEST_CASE(testHexagonSquare) {
    Point p1{-2, 0};
    Point p2{0, 2};
    Point p3{2, 0};
    Point p4{2, -1};
    Point p5{1, -2};
    Point p6{0, -2};
    Hexagon h{p1, p2, p3, p4, p5, p6};
    BOOST_CHECK_EQUAL(h.Square(), 9.5);
}
