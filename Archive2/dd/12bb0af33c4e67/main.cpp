#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/adaptor/map.hpp>
#include <boost/range/algorithm.hpp>

#include <iostream>
#include <ostream>

// ____________________________________________________________________________________________ //

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/range/iterator.hpp>
#include <iterator>

namespace impl
{

template<typename Iterator>
class cached_iterator : public boost::iterator_adaptor<cached_iterator<Iterator>,Iterator>
{
    typedef boost::iterator_adaptor<cached_iterator,Iterator> super;
    mutable bool invalidated;
    mutable typename std::iterator_traits<Iterator>::value_type cached;    
public:
    cached_iterator() : invalidated(true) {}
    cached_iterator(const Iterator &x) : super(x), invalidated(true) {}

    typename std::iterator_traits<Iterator>::value_type dereference() const
    {
        if(invalidated)
        {
            cached = *(this->base());
            invalidated=false;
            return cached;
        }
        else
        {
            return cached;
        }
    }
    void increment()
    {
        invalidated=true;
        ++(this->base_reference());
    }
    void decrement()
    {
        invalidated=true;
        --(this->base_reference());
    }
    void advance(typename super::difference_type n)
    {
        invalidated=true;
        (this->base_reference())+=n;
    }
};

template<typename Iterator> cached_iterator<Iterator> make_cached_iterator(Iterator it)
{
    return cached_iterator<Iterator>(it);
}

template< class R >
struct cached_range : public boost::iterator_range<cached_iterator<typename boost::range_iterator<R>::type> >
{
private:
    typedef boost::iterator_range<cached_iterator<typename boost::range_iterator<R>::type> > base;
public:
    typedef R source_range_type;
    cached_range( R& r )
        : base( make_cached_iterator(boost::begin(r)), make_cached_iterator(boost::end(r)) )
    { }
};

template<typename InputRange>
inline cached_range<const InputRange> cache(const InputRange& rng)
{
    return cached_range<const InputRange>(rng);
}

template<typename InputRange>
inline cached_range<InputRange> cache(InputRange& rng)
{
    return cached_range<InputRange>(rng);
}

struct cache_forwarder{};

cache_forwarder cached;

template< class InputRange >
inline cached_range<const InputRange>
operator|( const InputRange& r, cache_forwarder )
{
    return cache(r);
}

template< class InputRange >
inline cached_range<InputRange>
operator|( InputRange& r, cache_forwarder )
{
    return cache(r);
}

} // namespace impl

// ____________________________________________________________________________________________ //


struct OnlyEven
{
    typedef int argument_type;
    typedef std::pair<bool, int> result_type;
    result_type operator()(argument_type x) const
    {
        std::cout << "fun: " << x << std::endl;
        return std::make_pair(x % 2 == 0, x);
    }
} only_even;

int main()
{
    using namespace impl;
    using namespace boost::adaptors;
    using namespace std;

    int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto flt =  filtered([](std::pair<bool, int> x)->bool{ return x.first; });

    auto s = v | transformed(only_even) | cached | reversed | cached | flt | flt | flt | flt | flt | flt;

    boost::copy(s | map_values, ostream_iterator<int>(cout,"\n") );
    return 0;
}

