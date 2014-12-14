#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

struct A {
    int i = 0;
    virtual A& operator[](int i) { return *this; } 
    virtual void foo() {cout << "A";} 
}; 
struct B : A { 
    int j = 0;
    virtual A& operator[](int i) { return *this; } 
    void foo() { cout << "B"; } 
}; 
struct C { 
    unique_ptr<A> a; 
    C(A* a_) : a{a_} {} 
    A& operator[](int i) { return *a; }
};

int main()
{
    C a{new A{}}, b{new B{}};
    
    a[4].foo(), b[100].foo(); 
    
    //cout << b[100].j; // error
} 
