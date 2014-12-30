#include <functional>
#include <iostream>


class foo {
public:
    template<typename T>
    void bar(T&& t) {
        std::cout << "bar\n";
        doit(std::bind(&foo::template bar_cb<T>, this, std::forward<T>(t)));
    }
    
    template<typename T>
    void doit(T&& t) {
        std::cout << "doit\n";
        t();
    }
    
    template<typename T>
    void bar_cb(T&& t) {
        std::cout << "bar_cb\n";
        t();
    }
};


void lala() {
    std::cout << "lala\n";
}

class functor {
public:
    void operator()() {
        std::cout << "functor::operator()\n";
    }
};


int main() {
    foo f;
    functor fn;
    f.bar(fn);
    
    // how ca i do that?
    //f.bar(std::bind(lala)); // not possible to bind an function
    
    return 0;
}