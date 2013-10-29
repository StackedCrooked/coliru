#include <iostream>

#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/as_map.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/push_back.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/fusion/include/adapt_assoc_struct.hpp>
#include <boost/fusion/include/at_key.hpp>

namespace fusion=boost::fusion;
namespace mpl=boost::mpl;


struct A {
  int a;
  std::string b;
  struct keys {
    struct a;
    struct b;
  };
};

BOOST_FUSION_ADAPT_ASSOC_STRUCT(
    A,
    (int,  a, A::keys::a)
    (std::string, b, A::keys::b)
)

template <typename Struct, typename Index>
struct get_pair
{
    typedef fusion::pair<typename fusion::extension::struct_assoc_key<Struct,Index::value>::type,typename fusion::extension::access::struct_member<Struct,Index::value>::type> type;
};

template <typename Struct>
struct push_back_pair
{
    push_back_pair(Struct& instance_):instance(instance_){}
	
	template <typename Sig>
	struct result;
	
	template <typename This, typename State, typename Index>
	struct result<This(State,Index)>
	{
		typedef typename fusion::result_of::push_back<const State, typename get_pair<Struct,Index>::type >::type type;
	};
    
    template <typename State, typename Index>
    typename fusion::result_of::push_back<const State, typename get_pair<Struct,Index>::type >::type operator()(const State& state, Index)
    {
        return fusion::push_back(state,typename get_pair<Struct,Index>::type(fusion::at_c<Index::value>(instance)));
    }
    
    Struct& instance;
};

template <typename Struct>
struct get_map_from
{
	typedef mpl::range_c<unsigned, 0, fusion::result_of::size<Struct>::value > Indices;

	typedef typename fusion::result_of::as_map< typename fusion::result_of::fold<Indices,fusion::vector0<>,push_back_pair<Struct> >::type>::type type;
};

int main()
{
    A a1;
    a1.a=2;
    a1.b="hello";
	
	typedef mpl::range_c<unsigned, 0, fusion::result_of::size<A>::value > Indices;
    
    fusion::map<fusion::pair<A::keys::a,int>,fusion::pair<A::keys::b,std::string> > map1=fusion::as_map(fusion::fold(Indices(),fusion::vector0<>(),push_back_pair<A>(a1)));
	
	get_map_from<A>::type map2 = fusion::as_map(fusion::fold(Indices(),fusion::vector0<>(),push_back_pair<A>(a1)));
	
	std::cout << fusion::at_key<A::keys::a>(map1) << std::endl;
	std::cout << fusion::at_key<A::keys::b>(map2) << std::endl;
};

