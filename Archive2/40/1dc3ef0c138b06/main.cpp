
#include <iostream>     // std::cout

using namespace std;

struct A {
};

struct B : public A {
};

class C : public B {
};

class D {
};

template<typename T>
void foo(const T&);

template<typename T>
void foo(const T& val) {
    foo(static_cast<const A&>(val));
}

template<>
void foo<A>(const A&) {
    cout << "A" << endl;
}

template<class T> struct SomeClass;

template<>
struct SomeClass<A> {
    SomeClass() {
        cout << "A class" << endl;
    }    
};

template<class T>
struct SomeClass : public SomeClass<A> {
    SomeClass() {
        //cout << "T class" << endl;
        crutchFoo(static_cast<A*>((T*)0)); // (1)
    };
    private:
    
    // ничего не делающая функция, которая служит только для того, чтобы не было warning'а о том,
    // что возвращаемое (1) значение нигде не спользуется
    inline void crutchFoo(A*) {};
};



int main() {
    foo(A());
    foo(B());
    foo(C());
    //foo(D()); // error: D is not child of D
    
    SomeClass<A> someA;
    SomeClass<B> someB;
    SomeClass<C> someC;
    //SomeClass<D> someD; // error: D is not child of A
}