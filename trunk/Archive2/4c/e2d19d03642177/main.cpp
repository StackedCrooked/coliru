template < typename DERIVED, typename... BASE > struct crtp_helper ;

template < typename T > struct crtp_helper<T> { /* ... */ };

struct base : crtp_helper<base>
{
    virtual ~base() = default ;
    const base& get() const { return do_get() ; }
    protected: virtual const base& do_get() const = 0 ;
};

template < typename DERIVED, typename FIRST, typename... REST >
struct crtp_helper< DERIVED, FIRST, REST... > : virtual FIRST, virtual REST...
{
    const DERIVED& get() const { return dynamic_cast< const DERIVED& >( do_get() ) ; }
    protected: virtual const base& do_get() const override = 0 ;
    // ...
};

struct A : crtp_helper<A,base> {};
struct B : crtp_helper<B,base> {};
struct AB : crtp_helper<AB,A,B> {};

int main()
{
    struct A1 : A { protected: virtual const base& do_get() const override { return *this ; } };
    struct B1 : B { protected: virtual const base& do_get() const override { return *this ; } };
    struct AB1 : AB { protected: virtual const base& do_get() const override { return *this ; } };
    
    A1 a ; const A& ra = a.get() ;
    B1 b ; const B& rb = b.get() ;
    AB1 ab ; const AB& rab = ab.get() ;;
}
