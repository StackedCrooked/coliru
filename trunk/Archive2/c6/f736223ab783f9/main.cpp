#include <iostream>

template<class T>
struct Other {
    T x;
};

class Ctor1 {
public:
    Ctor1(const Other<int>& o) {
        std::cout << o.x << '\n';
    }
};

class Ctor2 {
public:
    template<class T> Ctor2(const Other<T>& o) {
        std::cout << o.x << '\n';
    }
};

int main(){
    Other<int> other{123};
    Ctor1 first     {other};
    Ctor2 second    {other};
}