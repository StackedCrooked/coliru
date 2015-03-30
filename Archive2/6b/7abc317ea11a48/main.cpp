#include <iostream>

template<typename T, size_t N>
using vector_t = T __attribute__((ext_vector_type(N)));

using float2 = vector_t<float,2>;
using float3 = vector_t<float,3>;
using float4 = vector_t<float,4>;

template<typename T, int N>
std::ostream& operator<<(std::ostream& os, const vector_t<T,N>& vec)
{
    os << "[";
    for (size_t i = 0; i < N-1; ++i)
        os << vec[i] << ", ";
    os << vec[N-1];
    os << "]";
    
    return os;
}

int main()
{
    float4 f4 = {1,2,3,4};
    auto test = f4.zxy * 3;
    
    std::cout << f4 << "\n";
    std::cout << test << "\n";
}
