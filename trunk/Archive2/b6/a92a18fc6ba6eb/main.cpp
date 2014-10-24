#include <iostream>

template<typename C, typename T, T C::*m>
struct PrintMember {
    C& obj;
    PrintMember(C& obj) : obj(obj) {};
    void print() { std::cout << "Member of containing class: " << obj.*m << std::endl; };
};

struct TestClass {
    int data;
    PrintMember<TestClass, int, &TestClass::data> pm;
    TestClass() : pm(*this){};
};

int main()
{
    TestClass tc;
    tc.data = 5;
    tc.pm.print();
}  