#include <iostream>
#include <typeinfo>

void foo() {

}

int main() {
    std::cout << typeid(foo).name() << '\n';
    return 0;
}
