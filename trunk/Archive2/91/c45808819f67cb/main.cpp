#include <iostream>
#include <string>
#include <vector>

class C {};
class B : public C {};
class A : public B {
public:
    A() : C() {}
};

int main() {

}