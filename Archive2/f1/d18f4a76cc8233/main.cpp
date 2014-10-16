#include <iostream>
#include <memory>
#include <functional>

struct A {
    int val;  
    A(int v) : val(v) {}
    void doSomething() const { std::cout << val << "\n"; }
};

A& obviouslyBadFunction() {
    A a(0);
    return a;  // Obviously returning a reference to a local variable is bad!
}

std::function<void()>
badFunArgs() {
    A a(0);
    return [&a]{ a.doSomething(); };  // Capture local variable in lambda by-reference, also bad.
}

std::function<void()>
funArgsByValue() {
    A a(1);
    return [a]{ a.doSomething(); };  // Capture by-value, OK.
}

std::function<void()>
funArgsBySharedPointer() {
    auto a = std::make_shared<A>(2);  
    return [a]{ a->doSomething(); };  // Capture shared_ptr by value, OK.
}

std::function<void()>
funArgsMoveCapture() {
    A local_a(3);
    
    // Move capture. Using generalized lambda capture. C++14 only    
    return [a = std::move(local_a)]{ a.doSomething(); }; 
}

auto  // std::function can't hold move-only types, have to use return type deduction. C++14 only.
funArgsUniquePtr() {
    auto local_a = std::make_unique<A>(4); 
    
    // Move capture of move-only type using generalized lamda capture. C++14 only.
    return [a(std::move(local_a))](){ a->doSomething(); };
}


int main() {

    auto func1 = funArgsByValue();
    func1();
    
    auto func2 = funArgsBySharedPointer();
    func2();
    
    auto func3 = funArgsMoveCapture();
    func3(); 
    
    auto func4 = funArgsUniquePtr();
    func4(); 
}
