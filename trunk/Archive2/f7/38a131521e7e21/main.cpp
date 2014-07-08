#include <iostream>

using namespace std;

class Base {

public:
    virtual ~Base() {}

    // Factory for Base class

    template<class T>
    static T* Create(int i) {
        static_assert(std::is_base_of<Base, T>::value, "Needs to be derived from Base");
        return new T(i);
    }

    virtual void say() = 0;

protected:
    Base(int i): i(i) { }
    int i;
};

class A: public Base {

    friend Base; // Allow Base to construct

public:
    using Base::Base;

    void say() { cout << "I am A and have a value of " << i << endl; }
};

class B: public Base {

    friend Base; // Allow Base to construct

public:
    using Base::Base;

    void say() { cout << "I am B and have a value of " << i << endl; }
};

int main(){
    cout << "I'm creating A." << endl;
    A* a = Base::Create<A>(1);
    a->say();

    cout << "I'm creating B." << endl;
    B* b = Base::Create<B>(2);
    b->say();

    return 0;
}