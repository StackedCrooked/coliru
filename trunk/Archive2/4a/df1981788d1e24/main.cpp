#include <functional>
#include <iostream>

template<typename T>
struct Foo{
    void operator()(){
        std::cout<<myRef.get();
    }

    Foo(std::reference_wrapper<T> ref):myRef(ref){};

    std::reference_wrapper<T> myRef;
};

int main(){
    int Value=0;
    Foo<int> foo(std::ref(Value));
    Value=1;
    foo();
}