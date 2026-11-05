#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class Queue{

    size_t tail = 0; // кол-о добавленных элементов + указывает туда, куда будет записан следующий элемент
    size_t head = 0; // кол-о извлеченных элементов + указывает на элмент, стоящий первый на выходе

    size_t capacity = 0;
    T* pMem = nullptr;

    size_t get_index(size_t ind) const noexcept { // ключевой момент. мы двигаемся не линейно, а как бы по кругу в одном массиве,
                                                  // и перезаписываем элементы на места где были старые, поэтому нужна функция, которая
                                                  // будет переводить ind >= capacity в рамки нашего массива
            
        return ind & (capacity - 1); // т к капасити у меня идет по степеням двойки, то % будет ~ &
    }

    void reallocate(){

        size_t new_capacity = capacity == 0 ? 4 : capacity * 2;

        T* tmp = new T[new_capacity];

        for (size_t i = head, j = 0; i < tail; i++, j++){  //делаем сразу по феншую - новая память сразу начинается с head
            tmp[j] = std::move(pMem[get_index(i)]);
        }

        delete []  pMem;
        
        tail = size(); // важно не перепутать их местами, т к если сначала занулить head, то size() посчитается не правильно
        head = 0;
        capacity = new_capacity;

        pMem = tmp;
    }   
    public:

    Queue() : capacity(4), pMem(new T[capacity]) {}

    ~Queue() { delete [] pMem;}

    size_t size() const noexcept { return tail - head; }

    bool empty() const noexcept { return tail == head; }

    bool full() const noexcept { return capacity == size();}

    T& front() {

        if (empty()){

            throw std::out_of_range("Queue is empty!");
        }

        return pMem[get_index(head)]; 
    }
    
    const T& front() const {

        if (empty()){

            throw std::out_of_range("Queue is empty!");
        }
        
        return pMem[get_index(head)]; 
    }

    T& back() {

        if (empty()){

            throw std::out_of_range("Queue is empty!");
        }
        return pMem[get_index(tail - 1)];
    }

    const T& back() const {

        if (empty()){

            throw std::out_of_range("Queue is empty!");
        }
        return pMem[get_index(tail - 1)];
    }

    void pop() {
        
        if (empty()){

            throw std::out_of_range("Queue is empty!");
        }

        head++;
    }

    void push(const T& value){

        if (full()){

            reallocate();
        }

        pMem[get_index(tail++)] = value;

    }

    void push(T&& value){

        if (full()){

            reallocate();
        }

        pMem[get_index(tail++)] = std::move(value);

    }
    // на всякий добиваем рул оф файл

    Queue(Queue&& queue) noexcept {

        pMem = queue.pMem;
        head = queue.head;
        tail = queue.tail;
        capacity = queue.capacity;

        queue.pMem = nullptr;
        queue.head = 0;
        queue.tail = 0;
        queue.capacity = 0;
    }

    Queue& operator=(Queue&& queue) noexcept{

        if (&queue == this) { return *this;}

        delete [] pMem;

        pMem = queue.pMem;
        head = queue.head;
        tail = queue.tail;
        capacity = queue.capacity;

        queue.pMem = nullptr;
        queue.head = 0;
        queue.tail = 0;
        queue.capacity = 0;

        return *this;
    }

   Queue(const Queue& queue) {
        capacity = queue.capacity;
        pMem = new T[capacity];

        for (size_t i = queue.head, j = 0; i < queue.tail; i++, j++) { 
            pMem[j] = queue.pMem[queue.get_index(i)];
        }

        head = 0;
        tail = queue.size();
    }

    Queue& operator=(const Queue& queue) {

        if (&queue == this) { return *this; }

        delete[] pMem;

        capacity = queue.capacity;
        pMem = new T[capacity];

        for (size_t i = queue.head, j = 0; i < queue.tail; i++, j++) { 
            pMem[j] = queue.pMem[queue.get_index(i)];
        }

        head = 0;
        tail = queue.size();

        return *this;
    }

};
