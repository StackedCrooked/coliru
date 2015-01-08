#include <iostream>
#include <functional>

typedef unsigned int uint;

uint ack(uint m, uint n) {
    if (m == 0)
        return n + 1;
    else if (m > 0 && n == 0)
        return ack(m-1, 1);
    else if (m > 0 && n > 0)
        return ack(m-1, ack(m,n-1));
}

void double_iterate(std::function<void(uint m, uint n)> func, uint x, uint y) {
    for (uint i = 0; i < x; ++i)
        for (uint j = 0; j < y; ++j)
            func(i, j);
}

int main() {
    auto printAck = [](uint i, uint j) {
        std::cout << "Ack: m = " << i << "; n = " << j << "; ack = " << ack(i, j) << std::endl;
    };
    
    int numberOfIterations = 5;
    double_iterate(printAck, numberOfIterations, numberOfIterations);

    return 0;
}