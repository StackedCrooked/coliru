#include <iostream>

struct S {
    virtual ~S() = default;  
};

template<typename T>
auto addSayHi() {
    struct Foo : T {
        void sayHi() {std::cout << "Hi";}  
    };
    
    return Foo{};
}

int main() {
    auto obj = addSayHi<S>();
    obj.sayHi();
}