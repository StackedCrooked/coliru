#include <iostream>     // std::cout
#include <functional>   // std::bind
#include <map>          // std::map
#include <iostream>

template <typename T>
struct Bindable {
    
    void bindFunction (int x, void(T::*newFn)()) {
        mFns.insert(std::make_pair(x,newFn));
    }
    void invokeFunction (int key) {
        (static_cast<T*>(this)->*mFns.at(key))();
    }

protected:
    std::map<int, void(T::*)()> mFns;
};

struct A : Bindable<A> {
    void funAone (void) {
        std::cout << "called funAone" <<std::endl;
    }
    void funAtwo (void) {
        std::cout << "called funAtwo" <<std::endl;
    }
};

struct B : Bindable<B> {
    void funBone (void) {
        std::cout << "called funBone" <<std::endl;
    }
    void funBtwo (void) {
        std::cout << "called funBtwo" <<std::endl;
    }
};

int main() {
    A a;
    B b;

    a.bindFunction(1, &A::funAone);
    a.bindFunction(2, &A::funAtwo);
    b.bindFunction(1, &B::funBone);
    b.bindFunction(2, &B::funBtwo);

    a.invokeFunction(1);
    a.invokeFunction(2);
    b.invokeFunction(1);
    b.invokeFunction(2);
}
