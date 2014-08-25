#include <iostream>
#include <utility>

template< typename T, T t >
class Delegate;

template< typename R, typename C, typename... Args, R(C::*F) (Args...)>
class Delegate< R(C::*)(Args...), F > {
public:
    template< typename... Ts >
    static R invoke(Ts&&... args) {
        C t;
        return (t.*F)(std::forward< Ts >(args)...);
    }
    
};


class Class {
public:
    void print(int v) {
        std::cout << "Class: " << v << std::endl;
    }
    
};

int main(int argc, char** argv) {
    Delegate< void (Class::*) (int), &Class::print >::invoke(1);
    
    return 0;
}