#include <iostream>

template<typename T>
void processPointer(T* ptr) { std::cout << "Hello!\n"; }

void processPointer(void*) = delete;

int main () {
    processPointer<void*>(nullptr);
}
