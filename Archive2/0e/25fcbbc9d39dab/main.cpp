#include <string>
#include <vector>
#include <iostream>

using namespace std;

class A {
    public:
    static const int CONST_A = 10;
    int func();
};
class B {
    public:
        static const int CONST_B = 20;
};

int A::func() {
    bool c = true;
    const int a = (c == true) ? B::CONST_B : CONST_A;
    return a;
}

int main() {
    std::cout << A().func();
}