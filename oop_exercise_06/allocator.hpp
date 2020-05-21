#pragma once

#include <iostream>
#include <type_traits>

#include "tvector.hpp"
#include "stack.hpp"

namespace allctr {

template<class T, size_t ALLOC_SIZE>
struct allocator_t {
    using value_type = T;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using is_always_equal = std::false_type;

    template<class U>
    struct rebind {
        using other = allocator_t<U, ALLOC_SIZE>;
    };

    allocator_t() : memory_pool_begin(new char[ALLOC_SIZE]), memory_pool_end(memory_pool_begin + ALLOC_SIZE),
        memory_pool_tail(memory_pool_begin) {std::cout<<"allocator constr\n";};

    allocator_t(const allocator_t&) = delete;
    allocator_t(allocator_t&&) = delete;

    
    ~allocator_t() {
        delete[] memory_pool_begin;
        std::cout << "allocator dest\n";
    }
    T* allocate(size_t n);
    void deallocate(T* ptr, size_t n);
private:
    char* memory_pool_begin;
    char* memory_pool_end;
    char* memory_pool_tail;
    cntrs::vector_t<char*> free_blocks;
};   

template<class T, size_t ALLOC_SIZE>
T* allocator_t<T, ALLOC_SIZE>::allocate(size_t n) {
    if(n != 1) {
        throw std::logic_error("Can't allocate arrays");
    }
    if(size_t(memory_pool_end - memory_pool_tail) < sizeof(T)) {
        if(free_blocks.getSize()) {
            auto it = free_blocks.begin();
            char* ptr = *it;
            free_blocks.erase(0);
            return reinterpret_cast<T*>(ptr);
        }
        throw std::bad_alloc();
    }
    T* result = reinterpret_cast<T*>(memory_pool_tail);
    memory_pool_tail += sizeof(T);
    return result;
}

template<class T, size_t ALLOC_SIZE>
void allocator_t<T, ALLOC_SIZE>::deallocate(T* ptr, size_t n) {
    if(n != 1) {
        throw std::logic_error("Can't allocate arrays");
    }
    if(ptr == nullptr) {
        return;
    }
    free_blocks.push_back(reinterpret_cast<char*>(ptr));
}
}
