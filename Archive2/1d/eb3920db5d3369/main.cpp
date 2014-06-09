#include <iostream>

struct S1 {
    int a;
    char b;
};

struct S2 {
    S1 s;
    char c;
};

// For the C++ fans
struct S3 : S1 {
    char c;
};

int main() {
    std::cout << sizeof(S1) << ' ' << sizeof(S2) << ' ' << sizeof(S3) << '\n';
    std::cout << alignof(S2);
}