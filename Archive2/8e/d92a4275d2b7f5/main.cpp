#include <iostream>

class Test {
    public:
        void Print() {std::cout<<"Hello!\n";}
};

int main() {
    ((Test*)nullptr)->Print();
    return 0;
}