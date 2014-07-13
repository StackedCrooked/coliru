#include <iostream>
using namespace std;

constexpr int foo(int n){
    return n;
}

template<unsigned n> void f();

int main(){
    int n;
    cin >> n;
    int p[foo(n)];
    f<sizeof(p)>(); // oops
    return 0;
}
