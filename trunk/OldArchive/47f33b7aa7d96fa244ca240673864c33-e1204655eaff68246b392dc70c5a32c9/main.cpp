#include <iostream>

using namespace std;

struct Foo {
    // Foo has a user-defined default constructor that does not initialize i
    Foo() {}
    int i;
};

int main() {
    Foo x{}; // value-initialize x
    cout << x.i << endl;
}