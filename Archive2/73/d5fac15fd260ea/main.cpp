template < typename DERIVED, typename RESULT_HOLDER, typename... BASE > struct crtp_helper ;

template < typename T, typename RESULT_HOLDER > struct crtp_helper<T, RESULT_HOLDER> { /* ... */ };

struct one { virtual ~one() = default ; };

struct base : crtp_helper< base, one >
{
    using result_type = one ;
    virtual ~base() = default ;
    const result_type& get() const { return do_get() ; }
    protected: virtual const result_type& do_get() const = 0 ;
};

template < typename T > struct result_is { using type = T ; }; // documentation helper

template < typename DERIVED, typename RESULT_HOLDER, typename FIRST, typename... REST >
struct crtp_helper< DERIVED, RESULT_HOLDER, FIRST, REST... > : virtual FIRST, virtual REST...
{
    using result_type = typename RESULT_HOLDER::type ;
    const result_type& get() const { return dynamic_cast< const result_type& >( do_get() ) ; }
    protected: virtual const result_type& do_get() const override = 0 ;
    // ...
};

struct two : virtual one {}; struct three : virtual two {}; struct four : virtual three {}; struct five : virtual four {};

struct A : crtp_helper< A, result_is<two>, base > {};
struct B : crtp_helper< B, result_is<three>, base > {};
struct C : crtp_helper< C, result_is<four>, base > {};
struct ABC : crtp_helper< ABC, result_is<five>, A,B,C > {};

template < typename T > struct canned_impl : T
{
    using result_type = typename T::result_type ;
    protected: virtual const result_type& do_get() const override
    { static result_type result ; return result ; }
};

int main()
{
    canned_impl<B> b ; const B::result_type& rb = b.get() ;
    canned_impl<ABC> abc ; const ABC::result_type& rabc = abc.get() ;
}
