#include <iostream>

struct monster {
    virtual ~monster() = default ;

    virtual int foo() const = 0 ;
    virtual int bar() const = 0 ;
    virtual int baz() const = 0 ;

    virtual int foo_bar() const = 0 ;
    virtual int foo_bar_baz() const = 0 ;
};

template < typename DERIVED, int FOO = 0 > struct foo_impl : virtual monster {
    static constexpr int foo_val = FOO ;
    virtual int foo() const override { return foo_val ; }
};

template < typename DERIVED, int BAR = 1 > struct bar_impl : virtual monster {
    static constexpr int bar_val = BAR ;
    virtual int bar() const override { return bar_val ; }
};

template < typename DERIVED, int BAZ = 2 > struct baz_impl : virtual monster {
    static constexpr int baz_val = BAZ ;
    virtual int baz() const override { return baz_val ; }
};

template < typename DERIVED > struct monster_impl : virtual monster {

    virtual int foo_bar() const override {
        auto derived = static_cast<const DERIVED*>(this) ;
        return derived->foo_val * 2 + derived->bar() * 3 ;
    }

    virtual int foo_bar_baz() const override {
        auto derived = static_cast<const DERIVED*>(this) ;
        return derived->foo() * 2 + derived->bar_val * 3 + derived->baz_val * 4 ;
    }
};

struct dragon : foo_impl<dragon,5>, bar_impl<dragon,7>, baz_impl<dragon,9>,
                 monster_impl<dragon> {};
int main()
{
    const monster& m = dragon{} ;
    std::cout << m.foo_bar_baz() << " - " << m.foo_bar() << " == "
               << dragon::baz_val * 4 << '\n' ;
}
