#include <string>

template<class T> struct A {
    typedef T t_type;
};

struct B : public A<std::string> {
    typedef t_type X;
};

int main() {}