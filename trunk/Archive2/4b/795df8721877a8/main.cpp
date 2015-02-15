#include <iostream>
#include <memory>
#include <cassert>

class A
{
public:
    virtual A* clone() = 0;
};

namespace detail {
    template <typename T>
    struct Cloner : A {
        using A::A; // For constructors
        virtual A* clone() override {return new T;}
    };
}

template <typename T>
struct Cloner : detail::Cloner<T> {
    using detail::Cloner<T>::Cloner; // For constructors
    
    // For callers 
    template <class=void>
    T* clone() {return static_cast<T*>(detail::Cloner<T>::clone());}
};

class B : public Cloner<B>
{
};

int main()
{
    std::unique_ptr<A> Ap = std::make_unique<B>();
    auto Bp = dynamic_cast<B*>(Ap->clone());
    assert( Bp );
    static_assert( std::is_same<decltype(Bp->clone()), B*>{}, "" );
}