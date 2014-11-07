#include <iostream>
using namespace std;

class A{
public:
    int x;
};
class B : public A{
public:
    B(){
        x = 123;
    }
};
class C : public A{
public:
    C(){
        x = 456;
    }
};
class D : public B, public C{
};

int main(){

    D foo;

    try{
        throw D();
    } catch (A& e){
        cout << e.x << endl;
    }
    
    
}
