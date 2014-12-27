#include <iostream>
using namespace std;

class A
{
    int x;
public:
    A() {
        cout<<"Default Constructor\n";
    }

    A(A&& a) : x(a.x){
        cout<<"Move Constructor\n";
        a.x=0;
    }

    A(const A& a){
        x=a.x;
        cout<<"Copy Constructor\n";
    }

    A fun(A a){
        return a;
    }
    
    A& operator=(A const&) = default;
    A& operator=(A     &&) = default;
};

int main()
{
    A a;
    A b;
    A c;
    c = a.fun(b);
}