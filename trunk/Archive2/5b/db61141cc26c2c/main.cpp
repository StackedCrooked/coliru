#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}

//-----------------------------
struct A {
    int member;
};

struct B {
	B() = default;
	B( int val ) : member { val } {} // error C2664: 'A::A(A &&)' : cannot convert argument 1 from 'int' to 'const A &'
	A member = { 1 }; // error C2664: 'A::A(A &&)' : cannot convert argument 1 from 'int' to 'const A &'
};

A global { 1 }; // compile already 