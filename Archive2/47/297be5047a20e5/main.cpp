#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/at_c.hpp>

// private implementation details
namespace detail{
// shorthand ...
template<class S>
struct fusion_size{ static const unsigned value = boost::fusion::result_of::size<S>::type::value; };

// classic compile-time counter
template<unsigned> struct uint_{};

template<class Seq, class Pred, class F>
void find_if(Seq&, Pred const&, F, uint_<fusion_size<Seq>::value>, int)
{ /* reached the end, do nothing */ }

template<class Seq, class Pred, class F, unsigned I>
void find_if(Seq& s, Pred const& pred, F f, uint_<I>, long){
    if(pred(boost::fusion::at_c<I>(s)))
    {
        f(boost::fusion::at_c<I>(s));
        return; // bail as soon as we find it
    }
    find_if(s, pred, f, uint_<I+1>(), 0);
}
} // detail::

template<class Seq, class Pred, class F>
void find_if(Seq& s, Pred const& pred, F f){
    detail::find_if(s, pred, f, detail::uint_<0>(), 0);
}

#include <iostream>
#include <boost/fusion/include/vector.hpp>

bool pred(int i){
    std::cout << "looking at " << i << "\n";
    return i == 20; 
}

void f(int i){ std::cout << i << "\n"; }

int main(){
  boost::fusion::vector<int, int, int> v(10,20,30);
  find_if(v, pred, f);
}