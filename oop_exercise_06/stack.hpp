#pragma once

#include <iterator>
#include <memory>
#include <iostream>

namespace cntrs {

template<class T, class Allocator = std::allocator<T>>
class stack_t {
private:
    struct node_t;
public:
    struct forward_iterator {
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
        forward_iterator(node_t* ptr) : ptr_(ptr) {};
        T& operator*();
        forward_iterator& operator++();
        forward_iterator operator++(int);
        bool operator==(const forward_iterator& it) const;
        bool operator!=(const forward_iterator& it) const;
        private:
            node_t* ptr_;
            friend stack_t;
    };

    forward_iterator begin();
    forward_iterator end();
    void insert(const forward_iterator& it, const T& value);
    void insert(const int& pos, const T& value);
    void erase(const forward_iterator& it);
    void erase(int pos);
    void pop();
    T top();
    void push(const T& value);
    stack_t() = default;
    stack_t(const stack_t&) = delete;
    stack_t& operator=(const stack_t&) = delete;
private:
    using allocator_type = typename Allocator::template rebind<node_t>::other;

    struct deleter {
        deleter(allocator_type* allocator) : allocator(allocator) {};

        void operator()(node_t* ptr) {
            if(ptr != nullptr) {
                std::allocator_traits<allocator_type>::destroy(*allocator, ptr);
                allocator->deallocate(ptr, 1);
            }
        }
        private:
            allocator_type* allocator;
    };

    struct node_t {
        T value;
        std::unique_ptr<node_t, deleter> nextNode{nullptr, deleter{&this->allocator}};
        forward_iterator next();
        node_t(const T& value, std::unique_ptr<node_t, deleter> next) : value(value), nextNode(std::move(next)) {std::cout<<"constructed node\n";};
    };   
    allocator_type allocator {};
    std::unique_ptr<node_t, deleter> head{nullptr, deleter{&this->allocator}};
    node_t* tail = nullptr;

};

template<class T, class Allocator>
typename stack_t<T, Allocator>::forward_iterator stack_t<T, Allocator>::node_t::next() {
    return nextNode.get();
}

template<class T, class Allocator>
T& stack_t<T, Allocator>::forward_iterator::operator*() {
    return ptr_->value;
}

template<class T, class Allocator>
typename stack_t<T, Allocator>::forward_iterator& stack_t<T, Allocator>::forward_iterator::operator++() {
    *this = ptr_->next();
    return *this;
}

template<class T, class Allocator>
typename stack_t<T, Allocator>::forward_iterator stack_t<T, Allocator>::forward_iterator::operator++(int) {
    forward_iterator old = *this;
    ++*this;
    return old;
}

template<class T, class Allocator>
bool stack_t<T, Allocator>::forward_iterator::operator!=(const forward_iterator& it) const {
    return ptr_ != it.ptr_;
}

template<class T, class Allocator>
bool stack_t<T, Allocator>::forward_iterator::operator==(const forward_iterator& it) const {
    return ptr_ == it.ptr_;
}

template<class T, class Allocator>
typename stack_t<T, Allocator>::forward_iterator stack_t<T, Allocator>::begin() {
    return head.get();
}

template<class T, class Allocator>
typename stack_t<T, Allocator>::forward_iterator stack_t<T, Allocator>::end() {
    return nullptr;
}

template<class T, class Allocator>
void stack_t<T, Allocator>::insert(const forward_iterator& it, const T& value) {
    node_t* ptr = this->allocator.allocate(1);
    std::allocator_traits<allocator_type>::construct(this->allocator, ptr, value, std::unique_ptr<node_t,
            deleter>(nullptr, deleter{&this->allocator}));
    std::unique_ptr<node_t, deleter> newNode(ptr, deleter{&this->allocator});
    if(head == nullptr) {
        head = std::move(newNode);
    } else if(head->nextNode == nullptr) {
        if(it.ptr_) {
            tail = head.get();
            newNode->nextNode = std::move(head);
            head = std::move(newNode);
        } else {
            tail = newNode.get();
            head->nextNode = std::move(newNode);
        }
    } else if(head.get() == it.ptr_) {
        newNode->nextNode = std::move(head);
        head = std::move(newNode);
    } else if(it.ptr_ == nullptr) {
        tail->nextNode = std::move(newNode);
        tail = newNode.get();
    } else {
        auto temp = this->begin();
        while(temp.ptr_->next() != it.ptr_) {
            ++temp;
        }
        
        newNode->nextNode = std::move(temp.ptr_->nextNode);
        temp.ptr_->nextNode = std::move(newNode);
    }
}

template<class T, class Allocator>
void stack_t<T, Allocator>::insert(const int& pos, const T& value) {
    int i = 0;
    auto temp = this->begin();
    if(pos == 0) {
        insert(temp, value);
        return;
    }
    while(i < pos) {
        if(temp.ptr_ == nullptr) {
            break;
        }
        ++temp;
        ++i;
    }
    if(i < pos) {
        throw std::logic_error("Out of bounds");
    }
    this->insert(temp, value);
}

template<class T, class Allocator>
void stack_t<T, Allocator>::erase(const forward_iterator& it) {
    if(it == nullptr) {
        throw std::logic_error("Invalid iterator");
    }
    if(head == nullptr) {
        throw std::logic_error("Deleting from empty list");
    }
    if(it == this->begin()) {
        head = std::move(head->nextNode);
    } else {
        auto temp = this->begin();
        while(temp.ptr_->next() != it.ptr_) {
            ++temp;
        }
        temp.ptr_->nextNode = std::move(it.ptr_->nextNode);
    }
}

template<class T, class Allocator>
void stack_t<T, Allocator>::erase(int pos) {
    auto temp = this->begin();
    int i = 0;
    while(i < pos) {
        if(temp.ptr_ == nullptr) {
            break;
        }
        ++temp;
        ++i;
    }
    if(temp.ptr_ == nullptr) {
        throw std::logic_error("Out of bounds");
    }
    erase(temp);
}

template<class T, class Allocator>
void stack_t<T, Allocator>::pop() {
    erase(this->begin());
}

template<class T, class Allocator>
T stack_t<T, Allocator>::top() {
    if(head) {
        return head->value;
    } else {
        throw std::logic_error("Stack is empty");
    }
}

template<class T, class Allocator>
void stack_t<T, Allocator>::push(const T& value) {
    insert(this->begin(), value);
}

}
