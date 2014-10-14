#include <iterator>
#include <type_traits>

template <typename T> class RingBuffer {
public:
    template <bool is_const = false> 
    class Iterator;
    // actual RingBuffer implementation here
};    

template <typename T>
template <bool is_const> 
class RingBuffer<T>::Iterator {
public:
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef typename std::conditional<is_const, const value_type*, value_type*>::type pointer ;
    typedef typename std::conditional<is_const, const value_type&, value_type&>::type reference ;
    typedef std::random_access_iterator_tag iterator_category;

    // a bunch of functions here
};


int main()
{
    RingBuffer<int>::Iterator<true> r;
}