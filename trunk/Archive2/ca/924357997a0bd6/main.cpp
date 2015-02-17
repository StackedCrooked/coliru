#include <iostream> 

typedef long long ll;
typedef long ll1;

void foo(unsigned ll) {
    std::cout << "1";
}

void foo(unsigned long ll1) {
    std::cout << "2";
}

void foo(unsigned long long) {
    std::cout << "3";
}

int main() {
    foo(2u);
    foo(2ul);
    foo(2ull);
}