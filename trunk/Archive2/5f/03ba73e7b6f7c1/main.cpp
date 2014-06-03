#include <iostream>

using namespace std;

// Forward declaration
template<class T> T* Create(int i);

class Base {
    public:
        template<class T>
        friend T* Create(int);
        virtual void say() = 0;

    protected:
        Base(int i): i(i) { }   // This won't compile
        int i;
};

// Factory for Base class
template<class T>
T* Create(int i){
    return new T(i);
}

class A: public Base {
    public:
        A(int i) : Base(i) {}
        void say() { cout << "I am A and have a value of " << i << endl; }
};

class B: public Base{
    public:
        B(int i) : Base(i) {}
        void say() { cout << "I am B and have a value of " << i << endl; }
};

int main(){
    cout << "I'm creating A." << endl;
    A* a = Create<A>(1);
    a->say();

    cout << "I'm creating B." << endl;
    B* b = Create<B>(2);
    b->say();

    return 0;
}
