#include <iostream>

class test {
public:
    struct {
        union {
            int arr[3];
            struct {int a, b, c;};
        };
    };
    test() : arr{0,1,2} {}
};

int main() {
    test a;
    std::cout << a.c << std::endl;;
}
