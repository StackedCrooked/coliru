#include <iostream>
#include <string>
#include <vector>

#include <type_traits>


// Compile time index calculations for symmetric matrices where the upper part is stored linearly
namespace details{
    
    template<typename T, T N, T R, T C, T L, typename = std::integral_constant <T, L>  >
    struct toRowColSym_impl{
        
        static_assert(L < N*N, "linear offset needs to be smaller or equal max index N*N-1");
        
        using res =         typename std::conditional< (L >= N) ,  
                                               toRowColSym_impl<T, N-1,R+1,C+1,L-N>,
                                               toRowColSym_impl<T, N,R,C+L,0>
                                             >::type;
        static const T i = res::i;
        static const T j = res::j;
    
    };
    
    template<typename T, T N, T R, T C, T L>
    struct toRowColSym_impl<T, N, R, C, L, std::integral_constant <T,0> >
    {
        static const T i = R;
        static const T j = C;
    };
    
    
    template<typename T, T R, T C, T N>
    struct toLinearSym_impl
    {
        static_assert(R < N && C < N, "row and col smaller then N");
        static const T i = R*N + C - R*(R+1)/2 ;
    };
}

/** Get the row and column of the linear index \p L of the upper part of a symetric matrix of size \p N */
template<std::size_t L, std::size_t N>
using toRowColSym = typename details::toRowColSym_impl<std::size_t, N,0,0,L>; // use meta::eval

/** Get the linear index of the element at row \p R and col \p C of the linear stored upper part of a symetric matrix of size \p N  */
template<std::size_t R, std::size_t C, std::size_t N>
using toLinearSym = details::toLinearSym_impl<std::size_t,R,C,N>;

int main()
{
    
     using res = toRowColSym<5,4>;
     std::cout << res::i << "," << res::j << std::endl;
     
     std::cout << toLinearSym<2,2,3>::i << std::endl;
    
}
