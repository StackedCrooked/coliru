#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/tuple/tuple_comparison.hpp>

namespace boost { namespace tuples {

    // MSVC might not require this
    template <typename T, typename U>
    inline void swap(boost::tuple<T&, U&> a, boost::tuple<T&, U&> b) noexcept {
        using std::swap;
        swap(boost::get<0>(a), boost::get<0>(b));
        swap(boost::get<1>(a), boost::get<1>(b));
    }

} }
  
namespace detail {
    template <class KI, class VI> struct helper { 
        using value_type = boost::tuple<typename std::iterator_traits<KI>::value_type, typename std::iterator_traits<VI>::value_type>;
        using ref_type   = boost::tuple<typename std::iterator_traits<KI>::reference,  typename std::iterator_traits<VI>::reference>; 

        using difference_type = typename std::iterator_traits<KI>::difference_type;
    };
}

template <typename KI, typename VI, typename H = typename detail::helper<KI, VI> > 
class dual_iter : public boost::iterator_facade<dual_iter<KI, VI>, // CRTP
    typename H::value_type, std::random_access_iterator_tag, typename H::ref_type, typename H::difference_type> 
{ 
public: 
    dual_iter() = default;
    dual_iter(KI ki, VI vi) : _ki(ki), _vi(vi) { } 

    KI _ki; 
    VI _vi; 

private: 
    friend class boost::iterator_core_access; 

    void increment() { ++_ki; ++_vi; } 
    void decrement() { --_ki; --_vi; } 

    bool equal(dual_iter const& other) const { return (_ki == other._ki); } 

    typename detail::helper<KI, VI>::ref_type dereference() const { 
        return (typename detail::helper<KI, VI>::ref_type(*_ki, *_vi)); 
    } 

    void advance(typename H::difference_type n) { _ki += n; _vi += n; } 
    typename H::difference_type distance_to(dual_iter const& other) const { return ( other._ki - _ki); } 
}; 

template <class KI, class VI> 
    dual_iter<KI, VI> make_dual_iter(KI ki, VI vi) { return {ki, vi}; }

#include <iostream>
using std::begin;
using std::end;

int main()
{
    int  keys[] = {   5,   2,   3,   1,   4 };
    char vals[] = { 'a', 'b', 'd', 'e', 'c' };

    std::sort(make_dual_iter(begin(keys), begin(vals)), 
              make_dual_iter(end(keys), end(vals)));

    std::copy(begin(keys), end(keys), std::ostream_iterator<int> (std::cout << "\nKeys:\t",   "\t"));
    std::copy(begin(vals), end(vals), std::ostream_iterator<char>(std::cout << "\nValues:\t", "\t"));
}
