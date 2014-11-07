#include <stdio.h>

class Test {
    public:
    Test() {
        printf("New instance of Test!");
    }
};


int main() {
    Test t();
}
