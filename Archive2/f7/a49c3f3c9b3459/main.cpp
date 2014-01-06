#include <iostream>

#if 0
typedef int A;
#else
struct A
{
    int i;
    A(int j) : i{j} {};
    A() = default;
};

std::ostream& operator << (std::ostream& os, const A& a) {
    os << a.i;
    return os;
}
#endif

int main() {
    A a[3] = { A(1) };
    std::cout << a[1] << ' ' << a[2] << '\n';
}
