#include <iostream>

using RingType = int;

void push(const RingType& aData) { 
    std::cout << 'a';
    push(std::forward<RingType>(RingType(aData)));
}

void push(RingType&& aData) {
   std::cout << "Hello, world\n";
}


int main() {
    const RingType a = 0;
    push(a);
}
