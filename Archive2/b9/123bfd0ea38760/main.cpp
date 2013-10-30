#include <iostream>
using namespace std;

template<class T> void bar(T t) { foo(t); }

struct F {};

int main() {
    F f;
    bar(f);
    return 0;
}

void foo(F) { cout << "foo(F)\n"; }