#include <type_traits>

template<class T, int N>
using  identity_discard = T;

template<class T, int End, int Cur = 0, int... Is>
struct foo : foo<T, End, Cur+1, Is..., Cur>
{
    using base = foo<T, End, Cur+1, Is..., Cur>;
    using base::deduce;
    
    template<class Ret>
    static auto deduce( Ret(*p)(identity_discard<T, Is>..., identity_discard<T, Cur>) )
    -> Ret(*)(identity_discard<T, Is>..., identity_discard<T, Cur>)
    {  return p;  }
};
template<class T, int End, int... Is>
struct foo<T, End, End, Is...>
{
    template<class U>
    static auto deduce(U p) -> U
    {  return p;  }
};



float sin(float);
double sin(double);
long double sin(long double);

float pow(float,float);
double pow(double,double);
long double pow(long double,long double);

//#include <cmath>

int main()
{
    //foo<double, 2>::deduce(std::sin);
    //foo<double, 2>::deduce(std::pow);
    foo<double, 2>::deduce(sin);
    foo<double, 2>::deduce(pow);
}