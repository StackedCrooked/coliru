#include <iostream>

union stuff {
    int x;
    float f;
    stuff(int a): x(a) {}
    stuff(float f): f(f) {}
    
    void print() {
        std::cout << "stuff\n";
    }
};

int main() {
    stuff x(10);
    x.print();
}
    