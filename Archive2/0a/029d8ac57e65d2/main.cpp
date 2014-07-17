#include <vector>
#include <memory>
#include <iostream>

class A{};
class B: public A{};
class C: public A{};

template<typename T>
void CustomDeleter(T *t)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    delete t;
}

int main()
{
    std::vector<std::unique_ptr<A, void(*)(A *)>> myArray;
    
    myArray.push_back(
        std::unique_ptr<A, void(*)(A *)>(new A(), [](A *a){ 
            CustomDeleter(a); }));
    myArray.push_back(
        std::unique_ptr<A, void(*)(A *)>(new B(), [](A *a){ 
            CustomDeleter(static_cast<B*>(a)); }));
    myArray.push_back(
        std::unique_ptr<A, void(*)(A *)>(new C(), [](A *a){ 
            CustomDeleter(static_cast<C*>(a)); }));
}