#include <boost/fusion/include/sequence.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/fusion/include/is_sequence.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits.hpp> 

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/foreach.hpp>

#include <type_traits>
#include <typeinfo>
#include <vector>
#include <list>

std::string type_name_to_recover = "";

template<typename type_t> 
struct is_container : public std::false_type {};

template<typename type_t, typename allocator_t> 
struct is_container < std::vector < type_t , allocator_t> > : public std::true_type {};

template<typename type_t, typename allocator_t> 
struct is_container < std::list < type_t , allocator_t> >  : public std::true_type {};

template <typename type_t> 
struct simple_serializer;


template <typename sequence_t, typename index_t> 
struct sequence_iterator
{
    typedef typename boost::fusion::result_of::value_at<sequence_t, index_t>::type current_type_t;
    typedef typename boost::mpl::next<index_t>::type next_index_t;
	typedef boost::fusion::extension::struct_member_name<sequence_t, index_t::value> type_name_t;

	static inline void read_json( boost::property_tree::ptree  &pt, sequence_t& sequence) 
	{
		type_name_to_recover = type_name_t::call();
		simple_serializer<current_type_t>::read_json(pt, boost::fusion::at<index_t>(sequence));
		type_name_to_recover = "";
		sequence_iterator<sequence_t, next_index_t>::read_json(pt, sequence);
	}

};


//tail of the sequence
template <typename sequence_t>
struct sequence_iterator<sequence_t, typename boost::fusion::result_of::size<sequence_t>::type > 
{
	static inline void read_json( boost::property_tree::ptree  &pt, sequence_t& sequence) { }
};

template < typename sequence_t >
struct sequence_iterator_final : sequence_iterator < sequence_t, boost::mpl::int_< 0 > > {};



////////////////////////////////////////////////////////
//Plain old types serializer
////////////////////////////////////////////////////////
template <typename type_t> 
struct serialize_pod
{
	typedef serialize_pod<type_t> type;

	static inline void read_json( boost::property_tree::ptree  &pt, type_t& t) 
	{
		auto v = pt.get_child(type_name_to_recover);
		t =  boost::lexical_cast<type_t>(v.data());
	}
};

////////////////////////////////////////////////////////
//Sequence serializer
////////////////////////////////////////////////////////

template <typename sequence_t> 
struct serialize_sequence 
{
	typedef serialize_sequence<sequence_t> type;

	static inline void read_json( boost::property_tree::ptree  &pt, sequence_t& sequence) 
	{
		sequence_iterator_final<sequence_t>::read_json(pt, sequence);
	}

};

////////////////////////////////////////////////////////
//Container serializer
////////////////////////////////////////////////////////
template <typename container_type_t> 
struct serialize_container 
{
	typedef serialize_container<container_type_t> type;

	template <typename type_t>
	static void read_json( boost::property_tree::ptree  &pt, std::vector<type_t> &t) 
	{
		std::string temp_name = type_name_to_recover;
		type_name_to_recover = "";
		BOOST_FOREACH( boost::property_tree::ptree::value_type &tree_node_value, pt.get_child(temp_name) )
		{
			boost::property_tree::ptree subtree = (boost::property_tree::ptree) tree_node_value.second ;
			if( subtree.empty() )
			{
                auto tree_node_y = subtree.data();
				type_t type_val;
				simple_serializer<type_t>::read_json(tree_node_y, type_val);
				t.push_back(type_val);
			}
			else
			{
                auto tree_node_x = subtree.data();
				type_t type_val;
                simple_serializer<type_t>::read_json(tree_node_x, type_val);
				t.push_back(type_val);
			}
		}
	}

};


template <typename type_t> 
struct resolve_serializer_type 
{
  typedef 
	typename boost::mpl::eval_if< boost::fusion::traits::is_sequence < type_t > , serialize_sequence < type_t > , 
	typename boost::mpl::eval_if< is_container < type_t > , boost::mpl::identity < serialize_container < type_t > >,
    serialize_pod < type_t >  >  > 
  ::type type;
};

//
template <typename type_t> 
struct simple_serializer : public resolve_serializer_type<type_t>::type { };




struct StructB
{
	int s;
	std::vector<int> vi_b; 
};

struct StructA
{ 
	int v;  
	std::vector<int> vi; 
	std::vector<StructB> lb;
};

BOOST_FUSION_ADAPT_STRUCT( StructB, (int , s) (std::vector<int>, vi_b) )
BOOST_FUSION_ADAPT_STRUCT( StructA, (int, v) (std::vector<int>, vi) (std::vector<StructB>, lb ) )


int main(int argc, char *argv[]) 
{

	StructA sa_in;

	std::string json_data = "{\"v\":20,\"vi\":[123,456,123],\"lb\":[{\"s\":999,\"vi_b\":[909,808]},{\"s\":888,\"vi_b\":[707]},{\"s\":777,\"vi_b\":[606,505,404,303]}]}";

	std::stringstream is(json_data);
	boost::property_tree::ptree pt;
	boost::property_tree::json_parser::read_json(is, pt);

	simple_serializer<StructA>::read_json( pt , sa_in);
}