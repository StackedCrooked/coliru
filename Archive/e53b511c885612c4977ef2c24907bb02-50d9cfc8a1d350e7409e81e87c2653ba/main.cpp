#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <list>

using namespace std;

struct A {
   A() { cout << "const"; }
   A(const A&) { cout << "copy"; }
   
   void operator=(const A&) { cout << "assign"; }
};

int main() {
    A b;
    A() = A(b);
}