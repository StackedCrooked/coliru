#include <iostream>
#include <iterator>
#include <vector>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>

// this version is conforming to the Standard
// but is not compatible with boost::transformed
struct MutableLambda1
{
    int delta;     
    template<class T> auto operator()(T elem) { return elem * delta++; }
};

// Instead, this version works with boost::transformed
// but is not conforming to the Standard
struct MutableLambda2
{
    mutable int delta;
    template<class T> auto operator()(T elem) const { return elem * delta++; }
};

template<class R, class F>
auto scale(R r, F f) 
{
    return r | boost::adaptors::transformed(f);
}

int main()
{
    // real capturing mutable lambda, will not work with boost::transformed
    auto lam = [delta = 1](auto elem) mutable { return elem * delta++; };        
    auto rng = std::vector<int>{ 1, 2, 3, 4 };
    
    //boost::copy(scale(rng, lam), std::ostream_iterator<int>(std::cout, ","));                 /* ERROR */
    //boost::copy(scale(rng, MutableLambda1{1}), std::ostream_iterator<int>(std::cout, ","));   /* ERROR */
    boost::copy(scale(rng, MutableLambda2{1}), std::ostream_iterator<int>(std::cout, ","));     /* OK!   */
}
