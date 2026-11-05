#pragma once

#include "forwardlist.h"
#include <cstddef>

template <typename T>
class Stack{

    ForwardList<T> list;
    size_t size = 0;

    public:

    void push(const T& value){

        list.push_front(value);
        size ++;
    }

    void push(T&& value){

        list.push_front(std::move(value));
        size++;
    }
    void pop(){

        if (size == 0){
           return;
        }
        list.pop_front();
        size--;
    }

    T& top(){

        return list.front();
    }

    const T& top() const {
        
        return list.front();
    }

    bool empty() const noexcept{

        return list.empty();
    }

    size_t get_size() const noexcept{

        return size;
    }

    void clear(){

        list.clear();
        size = 0;
    }

    


};