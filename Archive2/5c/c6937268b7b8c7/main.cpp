#include <iostream>
#include <complex>
#include <map>
#include <iterator>

using kv_pair_type = std::pair< int, std::complex<double> > ;

template < typename MAP_KEY >
struct kv_pair_iterator : std::iterator< std::input_iterator_tag, const kv_pair_type >
{
    explicit kv_pair_iterator( int k, MAP_KEY mk = MAP_KEY{} )
	    : map_key(mk), pair{ mk(k) } {}

	reference operator*() const { return pair ; }
	pointer operator->() const { return &**this ; }

	kv_pair_iterator& operator++()
	{
	    ++pair.first ;
	    pair = map_key( pair.first ) ;
	    return *this ;
    }

	kv_pair_iterator operator++(int)
	{ kv_pair_iterator temp(*this) ; ++*this ; return temp ; }

	bool operator== ( const kv_pair_iterator& that ) const { return pair == that.pair ; }
	bool operator!= ( const kv_pair_iterator& that ) const { return pair != that.pair ; }

	private:
	    const MAP_KEY map_key ;
	    kv_pair_type pair ;
};

template < typename MAP_KEY >
kv_pair_iterator<MAP_KEY> make_kvpi( int key, MAP_KEY map_key = MAP_KEY{} )
{ return kv_pair_iterator<MAP_KEY>{ key, map_key } ; }

int main ()
{
    struct make_kvpair
    { 
        kv_pair_type operator() ( int key ) const 
        { return { key, std::complex<double>( key*3 + 2, key*key ) } ; } 
    };

    using iterator = kv_pair_iterator<make_kvpair> ;

    std::map< int, std::complex<double> > map { iterator(1), iterator(10) } ;

    for( const auto& p : map ) std::cout << p.first << " => " << p.second << '\n' ;
}
