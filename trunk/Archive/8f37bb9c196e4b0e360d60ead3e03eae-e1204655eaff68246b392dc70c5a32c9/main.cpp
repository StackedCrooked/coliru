#include <iostream>
#include <typeinfo>

template <typename T, std::size_t N>
inline void force_static_array(const T (&)[N]) {}

int main() {
    using namespace std;
    const int n = 2;
    int m = 2;
    int a[2];
    int b[n];
    int c[m];

    cout << sizeof(a) << endl;
    cout << sizeof(b) << endl;
    cout << sizeof(c) << endl;
    
    cout << sizeof(decltype(a)) << endl;
    cout << sizeof(decltype(b)) << endl;
    cout << sizeof(decltype(c)) << endl;
    
    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;
    cout << typeid(c).name() << endl;
    
    force_static_array(a);
    force_static_array(b);
    force_static_array(c);
}