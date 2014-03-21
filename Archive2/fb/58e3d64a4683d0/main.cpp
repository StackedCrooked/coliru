#include <cstddef>
#include <iostream>

template<std::size_t... Ints> 
struct index_sequence;


template<class,class> struct transform;

template<std::size_t... Ints, class Op>
struct transform<index_sequence<Ints...>, Op>
{
    using type=index_sequence<Op()(Ints)...>;
};



template<std::size_t N>
struct sum
{
    static constexpr std::size_t value=sum<N-1>::value+N;
};

template<>
struct sum<0>
{
    static constexpr std::size_t value=0;
};



int main() {
    struct help : sum<250> {};
    
    std::cout << sum<500>::value << std::endl;
    
}