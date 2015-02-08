#include <iostream>

template<class T, const T& t>
void foo(){ std::cout << "foo()" << std::endl; }

class R
{
public:
    int f;
    constexpr R(): f(15){ }
};

const R r;

int main(){ foo<R, r>(); }