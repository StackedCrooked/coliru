#include <iostream>
#include <memory>
 
class A {
public:
    virtual ~A() = default;
    virtual void p() const { std::cout << "A" << std::endl; }
};
class B : public A {
public:
    virtual ~B() = default;
    virtual void p() const { std::cout << "B" << std::endl; }
};
 
int main()
{
    std::shared_ptr<A> pA = std::make_shared<B>();
    pA->p();
}