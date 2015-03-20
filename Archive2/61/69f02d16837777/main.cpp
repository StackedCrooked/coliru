#include <iostream>

// MyClass.hpp

class MyClass {
    friend struct MyClassHelper;
    int x;
    
public:
    MyClass(int x) : x(x) { }
    void test();
};

// MyClass.cpp

struct MyClassHelper {
    static void helperFn(MyClass& that) {
        std::cout << that.x << '\n';
    }
};

void MyClass::test() {
    MyClassHelper::helperFn(*this);
}

// Main.cpp

int main() {
    MyClass a(42);
    
    a.test();
}