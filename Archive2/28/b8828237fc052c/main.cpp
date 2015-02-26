#include <iostream>

namespace Y {
namespace X { 
    
template<int, bool> 
class B;    
    
template<int N>
class B<N, false> {};

template<int N>
bool operator==(B<N, false> const&, B<N, false> const&) 
{ std::cout << "==(B<N, false>, B<N, false>)\n"; return true; }

template<int N>
class B<N, true>: public B<N, false> {};

template<int N>
bool operator==(B<N, true> const&, B<N, true> const&) 
{ std::cout << "==(B<N, true>, B<N, true>)\n"; return true; }

}   // X

template<int N>
class D: public X::B<N, N % 2> {};

template<int N>
bool operator!=(D<N> const& L, D<N> const& R) 
{ std::cout << "!=(D<N>, D<N>)\n"; return !(L == R); }

}   // Y

int main()
{
    Y::D<1> d1, d2;
    
    auto lam = [](auto const& L, auto const& R){
        return L != R;
    };
    
    lam(d1, d2);
    
    Y::X::B<1, true> b1, b2;
    
    lam(b1, b2);
}