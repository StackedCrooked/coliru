#include <iostream>

using RingType = int;

void push(RingType&& aData) {
   std::cout << "Hello, world\n";
}

void push(const RingType& aData) { 
    // std::cout << 'a';
    push(std::forward<RingType>(RingType(aData)));
}

int main() {
    const RingType a = 0;
    push(a);
}
