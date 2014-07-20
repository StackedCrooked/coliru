#include <iostream>

struct Base {
    enum Test {
        TestA = 10,
        TestB = 20
    };
};
struct Derived : Base {
    enum Test {
        TestA = 30,
        TestB = 40
    };
};
void f(Base::Test arg) {
    std::cout << arg;
}
int main(){
    f(Base::TestA);
    f(Base::TestB);
    f(Derived::TestA);
    f(Derived::TestB);
    return 0;
}