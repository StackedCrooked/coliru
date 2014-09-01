#include <iostream>
void f() {
    try {
        throw;
    } catch(int i) {
        std::cout << "Vomited " << i;
    }
}
int main() {
    try {
        throw 1;
    } catch(...) {
        f();
    }
}