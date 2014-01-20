#include <functional>

void f(int, int, int){}

int main(){
    std::bind(f)(1,2,3);
}