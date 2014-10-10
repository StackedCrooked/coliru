#include <type_traits>
#include <utility>
#include <iostream>
struct A {
    int work(){ std::cout << "Work A" << std::endl; return 0; }
};

struct B {
    int work() {std::cout << "Work B" << std::endl;  return 0;}
};

struct ObjectManager {
    static void manage( A& ){std::cout << "Manage A" << std::endl; }
    // manage not defined for class B 
};

template<class T>
auto call_manage(T* t) -> decltype(ObjectManager::manage(*t)){
    return ObjectManager::manage(*t);
}

void call_manage(...) {}

template<class T>
void doStuff( T t ) {
    t.work();
    //....
    call_manage(std::addressof(t));
}

int main() {
A a;
B b;

doStuff(a);
doStuff(b);
}