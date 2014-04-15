#include <utility>

template<class T>
void loop_body(T&& t) {}


    template<typename...Args> 
    void do_in_order(Args&&...args) {  
        typedef int for_each[];
        for_each{((void)(args()),0)...,0};
    }    
    template<typename...Args> 
    void f(Args&&...args) {  
        do_in_order([&](){loop_body(std::forward<Args>(args));}...);
    }    


int main() {
    f(34, "HI");
}