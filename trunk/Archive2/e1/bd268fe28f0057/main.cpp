#include <iostream>
#include <memory>
#include <type_traits>

 struct Base
{
    virtual ~Base() = default;

    struct event
    {
        event(Base &b) : inst(b) {}

        virtual ~event() = default;

        virtual void f() = 0;

        virtual Base& instance() { return inst ; }

    private:
        Base &inst;
        
        ///////////////////////////////  added /////////////////////////////////////////////
        template < typename T > std::unique_ptr< typename T::event > actual() 
        { return std::unique_ptr< typename T::event >{ dynamic_cast< typename T::event* >(this) } ; }

        template < typename T > friend std::unique_ptr<typename T::event> get_event( T& object )
        {
            static_assert( std::is_base_of<Base,T>::value, "not a derived or same type" ) ;
            auto p = static_cast<Base&>(object).new_inner() ;
            return p ? p->template actual<T>() : std::unique_ptr<typename T::event> { nullptr } ;
        }
        ///////////////////////////////////////////////////////////////////////////////////
    };

    template < typename T > friend std::unique_ptr<typename T::event> get_event( T& object ) ;

    private: virtual event* new_inner() = 0; // ***  we can return a raw pointer; this is private *** 
};

struct Derived : virtual Base
{
    Derived(int x) : v{x} {}

    struct event : virtual Base::event
    {
        using Base::event::event ;

        virtual void f() { std::cout << "Derived::inner::f " << instance().v << '\n' ; }

        virtual void g(int x) { std::cout << "Derived::inner::g\n" ; instance().v = x ; } 

        virtual Derived& instance() { return dynamic_cast<Derived&>( Base::event::instance() ) ; } 
    };

    private: virtual Derived::event* new_inner() override { return new event{*this} ; } // *** private ***

    private: int v;
};

int main()
{
    Derived d {6};
    auto inner = get_event(d);
    inner->f();
    inner->g(7);
    inner->f();
}
