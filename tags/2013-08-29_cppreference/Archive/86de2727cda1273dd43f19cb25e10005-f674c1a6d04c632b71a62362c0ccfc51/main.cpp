#include <iostream>

void impl();

typedef void(*func_type)() ;
template<func_type func>
void templater() {
    func();
}

int main() {
    templater<impl>();
}

void impl() {
    std::cout << "works";
}