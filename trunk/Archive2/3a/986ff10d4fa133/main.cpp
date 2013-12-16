#include <initializer_list>

struct X{
    struct iterator{};
    X(std::initializer_list<int>){}
    template<class T>
    X(T a, T b){}
};

int main(){
    X x1 {1,2,3};
    X x2 { X::iterator{}, X::iterator{} };
}