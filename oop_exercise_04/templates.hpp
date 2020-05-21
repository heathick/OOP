#pragma once

#include <iostream>
#include <type_traits>
#include<tuple>

#include "vertex.hpp"

template<class T>
struct is_vertex : std::false_type {};

template<class T>
struct is_vertex<vertex_t<T>> : std::true_type {};

template<class T>
struct is_figurelike_tuple : std::false_type {};

template<class Head, class... Tail>
struct is_figurelike_tuple<std::tuple<Head, Tail...>> :
    std::conjunction<is_vertex<Head>,
      std::is_same<Head, Tail>...> {};

template<class Type, size_t SIZE>
struct is_figurelike_tuple<std::array<Type, SIZE>> :
    is_vertex<Type> {};

template<class T>
inline constexpr bool is_figurelike_tuple_v =
    is_figurelike_tuple<T>::value;

template<class T, class = void>
struct has_area_method : std::false_type {};

template<class T>
struct has_area_method<T,
  std::void_t<decltype(std::declval<const T>().area())>> :
    std::true_type {};

template<class T>
inline constexpr bool has_area_method_v =
    has_area_method<T>::value;

template<class T>
std::enable_if_t<has_area_method_v<T>, double>
    area(const T& figure) {
    return figure.area();
}

template<class T, class = void>
struct has_print_method : std::false_type {};


template<class T>
struct has_print_method<T,
  std::void_t<decltype(std::declval<const T>().print(std::cout))>> :
    std::true_type {};

template<class T>
inline constexpr bool has_print_method_v =
    has_print_method<T>::value;

template<class T>
std::enable_if_t<has_print_method_v<T>, void>
    print(const T& figure, std::ostream& os) {
    figure.print(os);
}

template<class T, class = void>
struct has_center_method : std::false_type {};

template<class T>
struct has_center_method<T,
  std::void_t<decltype(std::declval<const T>().center())>> :
    std::true_type {};

template<class T>
inline constexpr bool has_center_method_v =
    has_center_method<T>::value;

template<class T>
std::enable_if_t<has_center_method_v<T>, vertex_t<decltype(std::declval<const T>().center().x)>>
    center(const T& figure) {
    return figure.center();
}

template<size_t ID, class T>
double single_area(const T& t) {
    const auto& a = std::get<0>(t);
    const auto& b = std::get<ID - 1>(t);
    const auto& c = std::get<ID>(t);
    const double dx1 = b.x - a.x;
    const double dy1 = b.y - a.y;
    const double dx2 = c.x - a.x;
    const double dy2 = c.y - a.y;
    return std::abs(dx1 * dy2 - dy1 * dx2) * 0.5;
}

template<size_t ID, class T>
double recursive_area(const T& t) {
  if constexpr (ID < std::tuple_size_v<T>){
        return single_area<ID>(t) + recursive_area<ID + 1>(t);
    } else {
        return 0;
    }
}

template<class T>
std::enable_if_t<is_figurelike_tuple_v<T>, double>
    area(const T& fake) {
    return recursive_area<2>(fake);
}

template<size_t ID, class T>
double single_center_x(const T& t) {
    return std::get<ID>(t).x / std::tuple_size_v<T>;
}

template<size_t ID, class T>
double single_center_y(const T& t) {
    return std::get<ID>(t).y / std::tuple_size_v<T>;
}

template<size_t ID, class T>
double recursive_center_x(const T& t) {
    if constexpr (ID < std::tuple_size_v<T>) {
        return single_center_x<ID>(t) + recursive_center_x<ID + 1>(t);
    } else {
        return 0;
    }
}

template<size_t ID, class T>
double recursive_center_y(const T& t) {
    if constexpr (ID < std::tuple_size_v<T>) {
        return single_center_y<ID>(t) + recursive_center_y<ID + 1>(t);
    } else {
        return 0;
    }
}

template<class T>
std::enable_if_t<is_figurelike_tuple_v<T>, vertex_t<double>>
    center(const T& tup) {
        return {recursive_center_x<0>(tup), recursive_center_y<0>(tup)};
}

template<size_t ID, class T>
void single_print(const T& t, std::ostream& os) {
    os << std::get<ID>(t) << ' ';
}

template<size_t ID, class T>
void recursive_print(const T& t, std::ostream& os) {
    if constexpr (ID < std::tuple_size_v<T>) {
        single_print<ID>(t, os);
        recursive_print<ID + 1>(t, os);
    } else {
        return;
    }
}

template<class T>
std::enable_if_t<is_figurelike_tuple_v<T>, void>
    print(const T& tup, std::ostream& os) {
        recursive_print<0>(tup, os);
        os << std::endl;
}
