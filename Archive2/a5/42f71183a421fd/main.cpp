

#include <iostream>

using namespace std;

//template<typename T>
struct A {
    template<typename U>
    bool operator()(U u) {
        cout << "all" << endl;
        return false;
    }
};

//template<typename T>
template<>
bool A::operator()<int>(int) {
    cout << "int" << endl;
    return false;
}

template<typename T>
struct B {
    template<typename U>
    void foo(U u) {
        cout << "all new" << endl;
    }
    
    void foo(int) {
        cout << "int new" << endl;
    };
};

template<>
template<>
void B<int>::foo<int>(int) {
    cout << "BIG int" << endl;
}

int main() {
    
    A a;
    a(10);
    a(10.);
    
    B<float> b;
    b.foo(10); 
    b.foo(10.);
    
    B<int> b1;
    b1.foo(10); // int new
    b1.foo<int>(10); // BIG int
    b.foo<int>(10); // all new
    
    return 0;
}