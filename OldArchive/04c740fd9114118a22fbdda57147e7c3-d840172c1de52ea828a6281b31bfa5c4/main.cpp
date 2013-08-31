#include <iostream>
#include <new> //std::nothrow
#include <cstddef> //std::size_t
#include <stdexcept>
#include <initializer_list>

template<typename T>
class Deque {
private:
    struct node {
        T data;
        node* prev;
        node* next;
        node(const T& t, node* prev, node* next): data(t), prev(prev), next(next) {}
    };
    node* head, *tail;
    size_t arr_size;
public:
    Deque() noexcept: head(nullptr), tail(nullptr), arr_size(0) {}
    Deque(std::initializer_list<T> list) noexcept: head(nullptr), tail(nullptr), arr_size(0) {
        for(auto&& i : list)
            push_back(i);
    }
    ~Deque() noexcept {
        while(head != nullptr) {
            node* temporary(head);
            head = head->next;
            delete temporary;
        }
    }

    bool empty() const {
        return (head == nullptr || tail == nullptr);
    }

    T& operator[](int index) {
        if(index == 0)
            return head->data;
        else if(index > 0) {
            int i = index;
            node* temporary(head);
            while(i > 0 && temporary != nullptr) {
                --i;
                temporary = temporary->next;
            }
            return temporary->data;
        }
        else if(index == -1)
            return tail->data;
        else if(index < 0) {
            int i = index;
            node* temporary(tail);
            while(i < 0 && temporary != nullptr) {
                ++i;
                temporary = temporary->prev;
            }
            return temporary->data;
        }
        else
            throw std::out_of_range("Invalid range");
    }

    const T& operator[](int index) const {
        if(index == 0)
            return head->data;
        else if(index > 0) {
            int i = index;
            node* temporary(head);
            while(i > 0 && temporary != nullptr) {
                --i;
                temporary = temporary->next;
            }
            return temporary->data;
        }
        else if(index == -1)
            return tail->data;
        else if(index < 0) {
            int i = index;
            node* temporary(tail);
            while(i < 0 && temporary != nullptr) {
                ++i;
                temporary = temporary->prev;
            }
            return temporary->data;
        }
        else
            throw std::out_of_range("Invalid range");
    }

    explicit operator bool() const {
        return !empty();
    }

    size_t size() const {
        return arr_size;
    }

    void push_back(const T& t) {
        tail = new(std::nothrow) node(t,tail,nullptr);
        if(tail->prev != nullptr)
            tail->prev->next = tail;
        if(empty())
            head = tail;
        ++arr_size;
    }

    void push_front(const T& t) {
        head = new(std::nothrow) node(t,nullptr,head);
        if(head->next != nullptr)
            head->next->prev = head;
        if(empty())
            tail = head;
        ++arr_size;
    }

    T pop_back() {
        if(empty())
            throw std::out_of_range("Invalid range");
        node* temporary(tail);
        T t(tail->data);
        tail = tail->prev;
        if(tail != nullptr) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
        delete temporary;
        --arr_size;
        return t;
    }

    void pop_front() {
        if(empty())
            throw std::out_of_range("Invalid range");
        node* temporary(head);
        head = head->next;
        if(head != nullptr) {
            head->next = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete temporary;
        --arr_size;
    }
};

int main() {
    Deque<int> d = {1,2,3,4,5,6,7};
    d.push_back(8);
    d.push_front(0);
    for(size_t i = 0; i < d.size(); ++i) {
        std::cout << d[i] << ' ';
    }
}
