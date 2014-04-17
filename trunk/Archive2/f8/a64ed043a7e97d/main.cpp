#include <vector>
#include <list>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/mpl.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/fusion/include/at_c.hpp>

#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>

namespace container
{
    template <typename T> struct vector { typedef std::vector<T> type; };
    template <typename T> struct list   { typedef std::list<T> type; };
}

template<template <typename> class Container>
struct wrap_into_container
{
	template<typename T>
	struct map
	{
		typedef typename Container<T>::type type;
	};
};

int main ()
{
	namespace fusion = boost::fusion;
    namespace mpl = boost::mpl;
    
    typedef fusion::vector<int, float, int> vec_type;
	typedef mpl::transform<vec_type, wrap_into_container<container::vector>::map<mpl::_1> >::type wrapped_vec_type;

	wrapped_vec_type w;
    
    for (int i = 0; i < 10; ++i)
    {
        fusion::at_c<0>(w).push_back(i);
    }
    
    std::copy(fusion::at_c<0>(w).begin(), fusion::at_c<0>(w).end(), std::ostream_iterator<int>(std::cout));
}
