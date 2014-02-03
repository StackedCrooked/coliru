#include <iostream>

int someFunction(int &x, int c) {
    c=c-1;
    if(c==0) {
        return 1;
    }
    x=x+1;
    return x * someFunction(x,c);
}

int main() {
    int p = 5;
    std::cout << someFunction(p,p);
}