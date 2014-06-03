#include <iostream>

using namespace std;

class Base {
    protected:
        Base(int i): i(i) { }   // This won't compile
        int i;
};

class A: public Base {
    public:
        using Base::Base;
        void say() { cout << "I am A and have a value of " << i << endl; }
};

int main(){
    cout << "I'm creating A." << endl;
    A a(42);
    a.say();
}
