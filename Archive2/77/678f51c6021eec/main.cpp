#include <iostream>

struct base
{
    double length ;
    double width ;
    double height ;

    virtual ~base() {}

    void not_polymorphic() const { std::cout << "base::not_polymorphic\n" ; }
    virtual void polymorphic() const { std::cout << "base::polymorphic\n" ; }
};

void foo( const base& b, void (base::*pmfn)() const ) { (b.*pmfn)() ; }

int main()
{
    struct derived : base
    {
        void not_polymorphic() const /* hide */
        { std::cout << "derived::not_polymorphic (hides base::not_polymorphic)\n" ; }

        virtual void polymorphic() const override
        { std::cout << "derived::polymorphic (overrides base::polymorphic)\n" ; }
    };

    base b ;
    derived d ;

    void (base::*pmfn)() const = &base::not_polymorphic ;
    foo( b, pmfn ) ; // base::not_polymorphic
    foo( d, pmfn ) ; // base::not_polymorphic

    pmfn = &base::polymorphic ;
    foo( b, pmfn ) ; // base::polymorphic
    foo( d, pmfn ) ; // derived::polymorphic (overrides base::polymorphic)

}
