#include <iostream>
using namespace std;

struct foo {
    foo()  { cout << "foo constructed.\n"; }
    ~foo() { cout << "foo destroyed.\n"; }
};

struct bar {
    bar(foo t=foo{}) { }
};

int main(int argc, char **argv) {
    bar X[2]{};
    return 0;
}