#include <iostream>

class test {
public:
    union {
        int arr[3] {0,1,2};
        struct {int a, b, c;};
    };
};

int main() {
    test a;
    std::cout << a.c << std::endl;;
}
