#include <functional>

struct X{
    void foo(){}
};

int main(){
    auto f = &X::foo;
    auto r = std::ref(f);
    X x;
    r(x);
}