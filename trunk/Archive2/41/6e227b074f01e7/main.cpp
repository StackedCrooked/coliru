#include <vector>
#include <iostream>

using namespace std;

class A {
public:
    A()           { cout << "A::A" << endl; }        
    ~A()          { cout << "A::~A" << endl; }               
    A(const A& t) { cout <<"A::A(A&)" << endl; }              
    A(A&& t)      { cout << "A::A(A&&)" << endl; }            
};

class B {
public:
    vector<A> va;
    B(const vector<A>& va) : va(va) {};
};

int main(void) {
    B b({ A() });
    return 0;
}