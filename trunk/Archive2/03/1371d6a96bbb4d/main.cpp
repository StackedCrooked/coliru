#include <iostream>
using namespace std;
struct A {
    A() { cout << "default" << endl; }
    A(const A&) { cout << "copy" << endl; }
    A(A&&) { cout << "move" << endl; }

};
int main() {
//    A a{};
    auto aa = A{};
    return 0;
}
