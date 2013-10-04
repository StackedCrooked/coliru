#include <iostream>

template <class T> 
unsigned bit_sizeof(T unused) {
    long long a,b,c;
    T x;
    x^=x;
    x|=1;
    a=b=c=x;
    b<<=8;
    c<<=3;
    x=b;
    while (x) {
        a<<=1;
        b<<=c;
        c<<=1;
        x=b;
    }
    return a;
}

struct a {
    int x;
};

int main() {
    std::cout << bit_sizeof<int*>(nullptr);
}
    