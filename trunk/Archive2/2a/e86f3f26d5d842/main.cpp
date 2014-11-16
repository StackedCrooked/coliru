#include <iostream>

using namespace std;

struct A
{ 
    A(){ }
    A(const A&&){ cout << "A(const&&)" << endl; }
    A(const A&) = default;
};

A a;

A b = a;

int main() {
}