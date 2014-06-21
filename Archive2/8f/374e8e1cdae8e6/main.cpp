#include <iostream>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/reverse.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/copy_if.hpp>
#include <boost/mpl/modulus.hpp>

namespace mpl = boost::mpl ;

template < std::size_t... INDICES >
using index_pack = mpl::vector_c< std::size_t, INDICES... > ;

namespace detail
{
    struct print_
    {
        template < typename T > void operator() ( T v ) const { stm << v << ' ' ; }
        std::ostream& stm ;
    };
}

template < typename INT_SEQ_WRAPPER > std::ostream& print( std::ostream& stm = std::cout )
{
    stm << "[ " ;
    mpl::for_each<INT_SEQ_WRAPPER>( detail::print_{stm} ) ;
    return stm << ']' ;
}

template < typename INT_SEQ_WRAPPER > struct reverse
{
    using type = typename mpl::copy< typename mpl::reverse<INT_SEQ_WRAPPER>::type,
                                     mpl::back_inserter< index_pack<> > >::type ;
};

template < typename INT_SEQ_WRAPPER > struct select_odds
{
    using type = typename mpl::copy_if< INT_SEQ_WRAPPER,
                                        mpl::modulus< mpl::_1, mpl::int_<2> >,
                                        mpl::back_inserter< index_pack<> > >::type ;
};

template < typename INT_SEQ_WRAPPER_A, typename INT_SEQ_WRAPPER_B > struct cat
{
    using type = typename mpl::copy< INT_SEQ_WRAPPER_B,
                                     mpl::back_inserter<INT_SEQ_WRAPPER_A> >::type ;
};

int main()
{
    using pack = index_pack<0,1,2,3,4,5,6,7,8,9> ;
    print<pack>() << '\n' ;

    using rpack = reverse<pack>::type ;
    print<rpack>() << '\n' ;

    using opack = select_odds<rpack>::type ;
    print<opack>() << '\n' ;

    using pack2 = index_pack<51,53,55,57> ;
    print<pack2>() << '\n' ;
    using cpack = cat< pack2, opack >::type ;
    print<cpack>() << '\n' ;

    using rcpack = reverse<cpack>::type ;
    print<rcpack>() << '\n' ;

    // compose inline reverse( cat<>, ( select_odds<>, reverse<> ) )
    print< reverse<
                     cat<
                          index_pack<51,53,55,57>,
                          select_odds< reverse< index_pack<0,1,2,3,4,5,6,7,8,9> >::type >::type
                        >::type
                   >::type >( std::cout << "\ncomposed inline:\n" ) << '\n' ;
}
