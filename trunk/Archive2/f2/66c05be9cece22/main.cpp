#include <iostream>
#include <vector>
#include <functional>

class A {
public:
    float method1(float a) { return a; }
};

class B {
public:
    float method2(float a) { return a; }
    float anothermethod2(float a) { return a; }
};

class C {
public:
    float method3(float a) { return a; }
};

int main()
{
    std::vector<std::function<float(float)>> MethodsToCall;
    A a;
    B b;
    C c;

    using std::bind;
    using namespace std::placeholders;
    MethodsToCall.push_back(bind(&A::method1,        &a, _1));
    MethodsToCall.push_back(bind(&B::method2,        &b, _1));
    MethodsToCall.push_back(bind(&C::method3,        &c, _1));
    MethodsToCall.push_back(bind(&B::anothermethod2, &b, _1));

    for(auto&& F : MethodsToCall )
    {
        std::cout << F(3.5) << std::endl;
    }
    return 0;
}