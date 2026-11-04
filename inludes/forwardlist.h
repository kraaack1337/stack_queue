#include <cstddef>
#include <algorithm>

template <typename T>
class ForwardList{

    struct Node{

        T data;
        Node* next = nullptr;
        
    };

    Node* first = nullptr;

    public:

    void push_front(const T& value){ // вставка в начало

        Node* cur = new Node{value, nullptr};

        cur->next = first;
        first = cur;
    }

    void pop_front(){ // удаление начального элемента

        if (first != nullptr){

            Node* tmp = first->next; // запоминаем указатель второго элемента списка

            delete first;
            first = tmp;
        }
    }

    ForwardList() = default; 

    ForwardList(size_t n , const T& value = T()){

        for (size_t i = n; i > 0; i--){
            push_front(value);
        }
    }

    ForwardList(const ForwardList& forwl){
        
        if (forwl.first == nullptr) { return; }

        first = new Node{forwl.first->data, nullptr}; 
        Node* cur = first;
        
        Node* cur1 = forwl.first->next; //смотрим на следующий элемент после первого
        
        while (cur1 != nullptr){ 
            
            cur->next = new Node{cur1->data, nullptr}; // выделяем память под следующий элемент

            // итерируемся до двум указателям
            cur = cur->next; 
            cur1 = cur1->next;

        }  
    }

    ForwardList(ForwardList&& forwl) noexcept {
        
        first = forwl.first;
        forwl.first = nullptr;

    }

    ForwardList(size_t n , const T arr[]){

        for (size_t i = 0; i < n; i++){
            push_front(arr[i]);
        }
    }
    ~ForwardList(){

        while (first != nullptr){
            
            pop_front();
        }
    }

    ForwardList& operator=(ForwardList forwl){ // здесь вызывается конструктор копирования/перемещения, 
                                               // по ресурсам ~ перегрузке оператора с const& или с &&, зато проще и все в одном месте
        
        std::swap(first, forwl.first); 

        return *this;
        // т к время жизни forwl = время работы функции, то после ее завершения вызовется деструктор, который уничтожит forwl
    } 

    bool empty() const noexcept{

        return first == nullptr;
    }

    const T& front() const{
        return first->data;
    }

    T& front() {
        return first->data;
    }
};