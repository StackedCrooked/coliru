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
struct C : crtp_helper<C,base> {};
struct ABC : crtp_helper<ABC,A,B,C> {};

int main()
{
    struct B1 : B { protected: virtual const base& do_get() const override { return *this ; } };
    struct ABC1 : ABC { protected: virtual const base& do_get() const override { return *this ; } };
    
    B1 b ; const B& rb = b.get() ;
    ABC1 abc ; const ABC& rabc = abc.get() ;;
}
