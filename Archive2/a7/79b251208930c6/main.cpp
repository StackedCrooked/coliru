#include <iostream>     // std::cout
#include <functional>   // std::bind
#include <map>          // std::map
#include <iostream>
#include <type_traits>
#include <utility>

struct Bindable {    
    template <typename T, typename std::enable_if<std::is_base_of<Bindable, T>{}, int>::type = 0>
    void bindFunction (int x, void(T::*newFn)()) {
        mFns.insert(std::make_pair(x, std::bind(newFn, static_cast<T*>(this))));
    }
    void invokeFunction (int key) {
        mFns.at(key)();
    }
protected:
    std::map<int, std::function<void()>> mFns;
};

struct A : Bindable {
    void funAone (void) {
        std::cout << "called funAone" <<std::endl;
    }
    void funAtwo (void) {
        std::cout << "called funAtwo" <<std::endl;
    }
};

struct B : Bindable {
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
