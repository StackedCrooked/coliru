#include <iostream>

struct T {};
struct U {
    U(T) {}
};
void f(U, int);
template<typename T> void f(T t, ...);
int main () {    
    f(T(), 0);
}