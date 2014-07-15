#include <vector>
#include <utility>
#include <iostream>

using namespace std;

class A {
public:
    A()           { cout << "A::A" << endl; }        
    ~A()          { cout << "A::~A" << endl; }               
    A(const A& t) { cout <<"A::A(A&)" << endl; }              
    A(A&& t)      { cout << "A::A(A&&)" << endl; }            
};

template<class T>
void f(T t) { }

int main(void) {
    A a;
    
    auto list = { a };
    
    cout << "list constructed" << endl;
    auto list2 = list;
    f(list);
    f(std::move(list));
    return 0;
}