#include <iostream>
#include <new>
#include <utility>
 
template <typename... Args>
void f(void* p, Args&&... args) {
    new(p) int[3]{std::forward<Args>(args)...};
}
 
int main() {
    int* p = new int[3]();
    f(p, 1, 2, 3);
    for (int i = 0; i < 3; ++i) {
        std::cout << p[i] << ' ';
    }
}
