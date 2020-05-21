#pragma once

#include <iostream>
#include <memory>

const int GROWTH = 2;

namespace cntrs {

template <class T>
class vector_t {
public:
    using value_type = T;
    using iterator = T*;
    vector_t() : data(std::move(std::unique_ptr<T[]>(new T[GROWTH]))), size(0), allocated(GROWTH) {};
    vector_t(size_t size) : data(std::move(std::unique_ptr<T[]>(new T[size]))), size(0), allocated(size) {};
    void push_back(const T& item);
    void resize(size_t size);
    void erase(size_t pos);
    size_t getSize() const;
    T& operator[](size_t pos);
    iterator begin() const;
    iterator end() const;
private:
    std::unique_ptr<T[]> data;
    size_t size;
    size_t allocated;
};

template <class T>
void vector_t<T>::push_back(const T& item) {
    if(size == allocated) {
        this->resize(size * GROWTH);
    }
    data[size++] = item;
}

template <class T>
void vector_t<T>::resize(size_t size) {
    std::unique_ptr<T[]> newData(new T[size]);
    int n = std::min(size, this->size);
    for(int i = 0; i < n; ++i) {
        newData[i] = data[i];
    }
    data = std::move(newData);
    this->size = n;
    allocated = size;
}

template<class T>
void vector_t<T>::erase(size_t pos) {
    std::unique_ptr<T[]> newData(new T[allocated]);
    for(unsigned i = 0; i < size; ++i) {
        if(i < pos) {
            newData[i] = data[i];
        } else if(i > pos) {
            newData[i - 1] = data[i];
        }
    }
    data = std::move(newData);
    this->size--;
}

template<class T>
size_t vector_t<T>::getSize() const {
    return size;
}

template<class T>
T& vector_t<T>::operator[](size_t pos) {
    if(pos >= this->size) {
        throw std::out_of_range("out of range");
    }
    return data[pos];
}

template<class T>
typename vector_t<T>::iterator vector_t<T>::begin() const {
    return data.get();
}

template<class T>
typename vector_t<T>::iterator vector_t<T>::end() const {
    if(data) {
        return data.get() + size;
    }

    return nullptr;
}


}
