#include <iostream>
#include <string>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/sequence.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/bind.hpp>

namespace phx    = boost::phoenix;
namespace fusion = boost::fusion;
using namespace phx::arg_names;

struct mprint
{
    template<typename T>
    void operator()(const T& t) const
    {
        std::cout << t << std::endl;
    }
};

struct get_val1
{
    template <typename T>
	std::string operator()(const T& t) const
	{
		return t.val1_;
	}
};

struct TStruct
{
    std::string val1_;
    double      val2_;
    int         val3_;
    bool        val4_;
    TStruct( const std::string &val1, double val2, int val3, bool val4 ) :
        val1_(val1), val2_(val2), val3_(val3), val4_(val4) { }
};

template <typename Sequence>
void viewVal1( const std::string &dummy, Sequence& args )
{
	typedef fusion::transform_view<Sequence, get_val1> project;
    fusion::for_each(project(args,get_val1()), mprint() );
}

template <typename Sequence>
void viewVal2( const std::string &dummy, Sequence& args )
{
	typedef fusion::transform_view<Sequence,decltype(phx::bind(&TStruct::val2_,arg1))> project;
    fusion::for_each( project(args,phx::bind(&TStruct::val2_, arg1)), mprint() );
}

int main( int argc, char* argv[] )
{
    auto mdata = fusion::make_vector(
            TStruct( "test1", 2.3, 1, true ),
            TStruct( "test2", 3.3, 2, false ),
            TStruct( "test3", 4.3, 3, true )
    );

    viewVal1( "dummy", mdata );
    viewVal2( "dummy", mdata );

    return 0;
}