#include <string>
#include <iostream>
 
struct A {
    std::string s;
    A() : s("A test") {}
    A(const A& o) : s(o.s) { std::cout << "A's copy!\n";}
    A& operator=(A other) {
        std::cout << "A's assignment copy!\n";
        return *this;
    }
};
 
struct B {
     std::string s2; 
     B() : s2("B test") {}
     B(const B& o) : s2(o.s2) { std::cout << "B's copy!\n";}
};

struct C {
    C() : a0() {}
    void runLambda() {
        A a1 = A();
        B b1 = B();
        a0.s = "A0 test";
        auto func = [=]{
            std::cout << "Calling lambda: " << a0.s << "\n";
        };
        std::cout << "Lambda defined\n";
        func();
        std::cout << "Lambda called\n";
    }
    A a0;
};

int main()
{
 C c0 = C();
 c0.runLambda();
}