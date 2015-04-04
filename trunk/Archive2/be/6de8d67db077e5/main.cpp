#include <iostream>
#include <typeinfo>

struct base
{
    struct visitor { virtual ~visitor() = default ;  };

    virtual ~base() = default ;
    virtual void accept( visitor& ) = 0 ;

};

template < typename DERIVED > struct derive_from_base_helper : base
{
    struct visitor { virtual void visit( DERIVED& ) = 0 ; } ;

    virtual void accept( base::visitor& v ) override
    {
        try { dynamic_cast< visitor& >(v).visit( dynamic_cast< DERIVED& >( *this) ) ; }
        catch( const std::bad_cast& ) { /* ignore the exception: this visitor does not wish to visit us */ }
    }
};

struct A : derive_from_base_helper<A> {};
struct B : derive_from_base_helper<B> {};
struct C : derive_from_base_helper<C> {};
struct D : derive_from_base_helper<D> {};
struct E : derive_from_base_helper<E> {};

int main()
{
    A a ; B b ; C c ; D d ; E e ; D d1 ; B b1 ; D d2 ;
    base* objects[] = { &a, &b, &c, &d, &e, &d1, &b1, &d2 } ;

    struct abe_visitor : base::visitor, A::visitor, B::visitor, E::visitor // // visit only A, B, E
    {
        virtual void visit( A& ) override { std::cout << "abe_visitor::visit A\n" ; } ;
        virtual void visit( B& ) override { std::cout << "abe_visitor::visit B\n" ; } ;
        virtual void visit( E& ) override { std::cout << "abe_visitor::visit E\n" ; } ;
    } abe_v ;

    for( base* obj : objects ) obj->accept(abe_v) ;

    std::cout << "---------------\n" ;

    struct bcd_visitor : base::visitor, B::visitor, C::visitor, D::visitor // visit only B, C, D
    {
        virtual void visit( B& ) override { std::cout << "bcd_visitor::visit B\n" ; } ;
        virtual void visit( C& ) override { std::cout << "bcd_visitor::visit C\n" ; } ;
        virtual void visit( D& ) override { std::cout << "bcd_visitor::visit D\n" ; } ;
    } bcd_v ;

    for( base* obj : objects ) obj->accept(bcd_v) ;
}
