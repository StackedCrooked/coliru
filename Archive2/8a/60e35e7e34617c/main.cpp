struct test_base { protected: int i ; } ;

template < typename... T > struct basic_test {} ;

// T is a friend of basic_test<T>, so T can access base::i inherited by basic_test<T>
template < typename T > struct basic_test<T> : virtual test_base { friend T ; } ;

// make FIRST and recursively every type in REST... friends of a base class
template < typename FIRST, typename... REST >
struct basic_test<FIRST,REST...> : basic_test<FIRST>, basic_test<REST...> {} ;

// every type in ARGS... is a friend of some base class or other
// therefore, every type in ARGS.. can access base::i inherited by test<ARGS...>
template < typename... ARGS > struct test : basic_test<ARGS...> {} ;

struct D
{
    void foo( test<int,D,double>& test_int_D_double )
    {
        test_int_D_double.i = 100 ; // fine; D is a friend of basic_test<D>
        // test<int,D,double> inherits from basic_test<D>
        // members and friends of D can access base::i inherited by test<int,D,double>
    }

    void bar( test<int,double>& test_int_double )
    {
        test_int_double.i = -9999 ; // *** error: base::i is protected,
        // test<int,double> does not inherit from basic_test<D>
        // members or friends of D can't access base::i inherited by test<int,double>
    }
};