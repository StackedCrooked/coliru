#include <iostream>

using namespace std;

template<typename T>
void swap_ptr(T& a, T& b) {
    a ^= b;
    b ^= a;
    a ^= b;
}

int main() {
   int a = 1;
   int b = 2;
   
   swap_ptr<int>(a, b);
   
   cout<<a<<endl;
   cout<<b<<endl;
}
