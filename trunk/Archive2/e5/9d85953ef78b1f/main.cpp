#include <iostream>
using namespace std;

class Base {
public:
    Base() { cout << "Base constructed" << endl; }
    virtual ~Base() = 0; // 
};
Base::~Base() { cout << "Base destructed" << endl; }

class Derived : public Base {
    char *cp;
public:
    Derived() : cp(new char[100]) { cout << "memory allocated" << endl; }
    virtual ~Derived() { delete[] cp; cout << "memory freed" << endl; }
};


int main() {
    cout << "main started" << endl;
    Base *p = new Derived();
    delete p;
    cout << "main ending" << endl;
}   
