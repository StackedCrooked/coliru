#include <iostream>
#include <type_traits>

template<typename T>
void processPointer(T* ptr) { std::cout << "Hello!\n"; static_assert(std::is_same<void,T>::value,"Told ya."); }

void processPointer(void*) = delete;

int main () {
    processPointer<void>((void*)0);
}
