#include <iostream>

struct test {
    union {
        int arr[3] {0,1,2};
        struct {
            int a;
            int b;
            int c;
        };
    };
};

int main() {
    test a;
    std::cout << a.c << std::endl;;
}
