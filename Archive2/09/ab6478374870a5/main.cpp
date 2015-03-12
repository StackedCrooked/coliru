#include <iostream>
#include <boost/preprocessor.hpp>

#define FOO_MEMBERS ((int,i,10)) ((long,j,20))

struct Foo
{
    #define OP(s, data, elem) BOOST_PP_TUPLE_ELEM(3, 0, elem) \
                              BOOST_PP_TUPLE_ELEM(3, 1, elem) = \
                              BOOST_PP_TUPLE_ELEM(3, 2, elem);
    BOOST_PP_SEQ_FOR_EACH(OP, , FOO_MEMBERS)
    // expands to 
    //      int i = 10; long j = 20;
    #undef OP
    
    Foo() = default;
    
    #define OP(s, data, elem) (BOOST_PP_TUPLE_ELEM(3, 0, elem) BOOST_PP_TUPLE_ELEM(3, 1, elem))
    Foo(
        BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_FOR_EACH(OP, , FOO_MEMBERS))
        // expands to
        //      int i, long j
    ) :
    #undef OP

    #define OP(s, data, elem) (BOOST_PP_TUPLE_ELEM(3, 1, elem)(BOOST_PP_TUPLE_ELEM(3, 1, elem)))
    BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_FOR_EACH(OP, , FOO_MEMBERS))
    // expands to
    //      i(i), j(j)
    #undef OP
    {}
};

int main()
{
    {
        Foo f;
        std::cout << f.i << std::endl;
        std::cout << f.j << std::endl;
    }
    {
        Foo f{30, 40};
        std::cout << f.i << std::endl;
        std::cout << f.j << std::endl;
    }
}
