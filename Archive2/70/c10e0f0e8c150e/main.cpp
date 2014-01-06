
#include <iostream>

struct Type1;
struct Type2;

template<typename T>
struct strategy;

template<>
struct strategy<Type1> {
    static void show(){
        std::cout << "Type 1 strategy" << std::endl;
    }
};

template<>
struct strategy<Type2> {
    static void show(){
        std::cout << "Type 2 strategy" << std::endl;
    }
};

template<typename T>
struct implementation{
    typedef strategy<T> strat;
    void show(){
        strat::show();
    }
};

int main() {
    implementation<Type1> a;
    implementation<Type2> b;
    a.show(); b.show();
}