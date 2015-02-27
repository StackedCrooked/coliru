#include <iostream>
#include <cassert>
#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/multiset_of.hpp>

using std::ostream;

template <typename K, typename V>
struct bimultimap : boost::bimap<boost::bimaps::multiset_of<K>, boost::bimaps::set_of<V> > {};

template <typename K, typename V>
ostream& operator<<(ostream& os, const bimultimap<K, V>& bmm)
{
    if (bmm.empty())
        return os << "[-]";
    
    typename bimultimap<K, V>::left_map::const_iterator it = bmm.left.begin(), end = bmm.left.end();
    for ( ; it != end; ++it)
        os << '[' << it->first << '|' << it->second << ']';
    
    return os;
}

int main()
{
    typedef bimultimap<int, int>::value_type value_type;
    typedef bimultimap<int, int>::left_map   left_map;
	typedef bimultimap<int, int>::right_map  right_map;
	bimultimap<int, int> bmm;
	
    std::cout << bmm << '\n';
    
    // Insertion
	bmm.insert(value_type(1, 51));
	bmm.insert(value_type(1, 52));
	bmm.insert(value_type(2, 53));
	
    std::cout << bmm << '\n';
    
	// Replacement
	bmm.right.erase(51);
	assert(bmm.insert(value_type(3, 51)).second);
	
    std::cout << bmm << '\n';
    
    // Search for values by key (result is iterator to the start of elements with matching key)
	{
        left_map::const_iterator it = bmm.left.find(1);
        assert(it != bmm.left.end());
        std::cout << it->second << '\n';
	}
    
	// Search for key by value (result is unique value)
	{
        right_map::const_iterator it = bmm.right.find(52);
        assert(it != bmm.right.end());
        std::cout << it->second << '\n';
	}
}
