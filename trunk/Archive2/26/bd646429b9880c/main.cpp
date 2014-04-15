#include <boost/fusion/include/sequence.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/fusion/include/is_sequence.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits.hpp> 

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <type_traits>
#include <typeinfo>
#include <vector>
#include <list>

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

	static inline void save( boost::archive::text_oarchive &oa, sequence_t& sequence) 
	{
		simple_serializer<current_type_t>::save(oa, boost::fusion::at<index_t>(sequence));
		sequence_iterator<sequence_t, next_index_t>::save(oa, sequence);
	}

	static inline void load( boost::archive::text_iarchive &ia, sequence_t& sequence) 
	{
		simple_serializer<current_type_t>::load(ia, boost::fusion::at<index_t>(sequence));
		sequence_iterator<sequence_t, next_index_t>::load(ia, sequence);
	}

};


//tail of the sequence
template <typename sequence_t>
struct sequence_iterator<sequence_t, typename boost::fusion::result_of::size<sequence_t>::type > 
{
	static inline void save(boost::archive::text_oarchive &oa, sequence_t& sequence) { }
	static inline void load(boost::archive::text_iarchive &ia, sequence_t& sequence) { }
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

	static void save(boost::archive::text_oarchive &oa, type_t &t) 
	{ 
		oa << t;
	}

	static void load(boost::archive::text_iarchive &ia, type_t &t) 
	{ 
		ia >> t;
	}
};

////////////////////////////////////////////////////////
//Sequence serializer
////////////////////////////////////////////////////////
struct serialize_sequence_save 
{
	boost::archive::text_oarchive &oa;
	serialize_sequence_save(boost::archive::text_oarchive &oa_):oa(oa_) {}
	
	template <typename type_t> 
	void operator()(type_t& t) const
	{
		simple_serializer<type_t>::save(oa , t);
	}

	template <typename type_t> 
	void operator()(type_t& t, typename std::enable_if< boost::fusion::traits::is_sequence <type_t>::value >::type* = 0 ) const
	{
		serialize_sequence_save save_fn(oa);
		save_fn(t);
	}

};

struct serialize_sequence_load
{
	boost::archive::text_iarchive &ia;
	serialize_sequence_load(boost::archive::text_iarchive &ia_):ia(ia_) {}

	template <typename type_t> 
	void operator()(type_t& t) const
	{
		simple_serializer<type_t>::load(ia,t);
	}
};

template <typename sequence_t> 
struct serialize_sequence 
{
	typedef serialize_sequence<sequence_t> type;

	static void save(boost::archive::text_oarchive &oa, sequence_t &sequence) 
	{
		sequence_iterator_final<sequence_t>::save(oa, sequence);
		//boost::fusion::for_each(sequence, serialize_sequence_save(oa));
	};

	static void load(boost::archive::text_iarchive &ia, sequence_t &sequence) 
	{
		boost::fusion::for_each(sequence, serialize_sequence_load(ia));
	};

};

////////////////////////////////////////////////////////
//Array serializer
////////////////////////////////////////////////////////
template <typename array_type_t> 
struct serialize_array 
{
	typedef serialize_array<array_type_t> type;
	typedef typename boost::remove_bounds<array_type_t>::type slice_t;
	static const size_t size = sizeof(array_type_t) / sizeof(slice_t);

	static inline void save(boost::archive::text_oarchive &oa, array_type_t & t) 
	{
		for(size_t idx=0; idx<size; idx++) 
		{ 
			simple_serializer<slice_t>::save(oa, t[idx]); 
		}
	}

	static inline void load(boost::archive::text_iarchive &ia, array_type_t & t) 
	{
		for(size_t idx=0; idx<size; idx++) 
		{ 
			simple_serializer<slice_t>::load(ia, t[idx]); 
		}
	}
};

////////////////////////////////////////////////////////
//Container serializer
////////////////////////////////////////////////////////
template <typename container_type_t> 
struct serialize_container 
{
	typedef serialize_container<container_type_t> type;

	/////////////////////////////////////////////////
	// std::vector serialization
	/////////////////////////////////////////////////
	template <typename type_t>
	static void save(boost::archive::text_oarchive &oa, std::vector<type_t> &t) 
	{ 
		int vector_size = t.size();
		oa << vector_size;
		std::for_each (	t.begin(), 
						t.end(), 
						([&](type_t &type_value)
							{
								serialize_pod<type_t>::save(oa, type_value);
							}
						));
	}

	template <typename type_t>
	static void load(boost::archive::text_iarchive &ia, std::vector<type_t> &t) 
	{ 
		int vector_size = 0;
		type_t value_;

		ia >> vector_size;
		t.reserve(vector_size);

		for(auto i=0;i<vector_size;++i)
		{
			ia >> value_;
			t.push_back(value_);
		}
	}

	/////////////////////////////////////////////////
	// std::list serialization
	/////////////////////////////////////////////////
	template <typename type_t>
	static void save(boost::archive::text_oarchive &oa, std::list<type_t> &t) 
	{ 
		int list_size = t.size();
		oa << list_size;
		std::for_each (	t.begin(), 
						t.end(), 
						([&](type_t &type_value)
						{
							serialize_pod<type_t>::save(oa, type_value);
						}
		));
	}

	template <typename type_t>
	static void load(boost::archive::text_iarchive &ia, std::list<type_t> &t) 
	{ 
		int list_size = 0;
		type_t value_;

		ia >> list_size;

		for(auto i=0;i<list_size;++i)
		{
			ia >> value_;
			t.push_back(value_);
		}
	}
};


template <typename type_t> 
struct resolve_serializer_type 
{
  typedef 
	typename boost::mpl::eval_if< boost::fusion::traits::is_sequence < type_t > , serialize_sequence < type_t > , 
	typename boost::mpl::eval_if< boost::is_array < type_t > , boost::mpl::identity< serialize_array < type_t > >,
	typename boost::mpl::eval_if< is_container < type_t > , boost::mpl::identity < serialize_container < type_t > >,
    serialize_pod < type_t >  >  >  >
  ::type type;
};

//
template <typename type_t> 
struct simple_serializer : public resolve_serializer_type<type_t>::type { };



struct StructB
{
	int s;
};

struct StructA
{ 
	int v;  
	std::vector<int> vi; 
	std::list<StructB> lb;
};

BOOST_FUSION_ADAPT_STRUCT( StructB, (int , s) )
BOOST_FUSION_ADAPT_STRUCT( StructA, (int, v) (std::vector<int>, vi) (std::list<StructB>, lb ) )






int main(int argc, char *argv[]) 
{

	StructA sa_in, sa_out;
	sa_in.v = 20;
	sa_in.vi.push_back(123);
	sa_in.vi.push_back(456);
	sa_in.vi.push_back(123);
	
	StructB sb1, sb2, sb3;
	sb1.s = 999; sb2.s = 888 ; sb3.s = 777;

	sa_in.lb.push_back(sb1);
	sa_in.lb.push_back(sb2);
	sa_in.lb.push_back(sb3);
	
	std::ostringstream os;
	boost::archive::text_oarchive oa(os);
	simple_serializer<StructA>::save(oa, sa_in);
	
	std::string data = os.str();
	std::cout << data << std::endl;
}