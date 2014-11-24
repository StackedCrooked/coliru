#include<iostream>

struct Base {
//  template <typename T> virtual void foo() = 0;  // illegal
    virtual void foo (class Visitor& visitor) = 0;  // The attempted solution
};

template <typename D>
struct Derived : Base {
    virtual void foo (Visitor&) override;
};


struct Type1 {};
//...
struct TypeN {};

struct Visitor {
    virtual ~Visitor() {}

    virtual void visit (Base*) const = 0;
    virtual void visit (Derived<Type1>* d) const { this->visit(static_cast<Base*>(d)); };
    //...
    virtual void visit (Derived<TypeN>* d) const { this->visit(static_cast<Base*>(d)); };
};


struct FooVisitor : public Visitor
{
    virtual void visit (Base* base) const { std::cout<<"visiting base class."<<std::endl;}

    //further define visit for those types that require a different implementation
    virtual void visit (Derived<TypeN>* d) const { std::cout<<"visiting class of type Derived<TypeN>."<<std::endl;}
};
    
template <typename D>
void Derived<D>::foo (Visitor& visitor) {visitor.visit(this);}

int main()
{
    FooVisitor v;

    Derived<Type1> d1;
    d1.foo(v);

    Derived<TypeN> dN;
    dN.foo(v);

}
    
