
#include <array>

template< typename T1, typename T2 , typename T3 = int>
struct A;

template<typename T, unsigned int N, typename T2, typename T3>
struct A< std::array<T,N>, T2,  T3 > {
    int a;
};

int main()
{
  A< std::array<int,10>, double>  a;
  a.a +=3;
}
