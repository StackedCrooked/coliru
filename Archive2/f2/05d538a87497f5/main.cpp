#include <set>
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

struct A {
    int64_t a;
    int32_t b;
    int8_t c;
};

struct B {
    int32_t a;
};

int main () {
    cout << sizeof(struct { int64_t a; int32_t b; int8_t c; ) << endl;
    cout << sizeof(B) << endl;
}