#include <iostream>
using namespace std;

struct foo {
    foo()  { cout << "foo constructed.\n"; }
    ~foo() { cout << "foo destroyed.\n"; }
};

struct bar {
    bar(foo =foo{}) { }
};

int main() {
    bar X[2]{};
    return 0;
}