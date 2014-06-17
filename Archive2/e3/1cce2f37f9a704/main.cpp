#include <future>
#include <thread>
#include <iostream>
#include <utility>

template<class T>
class AsynchronicallyDestroyed {
    T* t;
    
public:
    template<typename... Args>
    AsynchronicallyDestroyed(Args&&... args) : t(new T(std::forward<Args>(args)...)) { }
    
    ~AsynchronicallyDestroyed() {
        std::async(std::launch::async, [this]() { delete t; });
    }
};

class C {
public:
    C() {
        std::cout << "default ctor\n";
    }
    C(C const&) {
        std::cout << "copy ctor\n";
    }
    ~C() {
        std::cout << "default dtor\n";
    }
};

int main () {
    AsynchronicallyDestroyed<C> c;
}