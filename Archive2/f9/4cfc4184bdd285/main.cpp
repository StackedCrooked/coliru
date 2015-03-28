#include <iostream>
#include <memory>
#include <vector>
 
template < size_t... T >
struct Mul;
 
template < size_t Head, size_t... Leafs >
struct Mul<Head,Leafs...> {
    static constexpr size_t value = Head * Mul<Leafs...>::value;
};
 
template <>
struct Mul< > {
    static constexpr size_t value = 1;
};
 
template <size_t... Dims, typename... Indices>
size_t Index( Indices... indices );
 
template <size_t Dims, typename Indices>
size_t Index( Indices indices ) {
    return indices;
}
template <size_t Dim, size_t... Dims, typename First, typename... Indices>
size_t Index( First first, Indices... indices ) {
    return first * Mul<Dims...>::value + Index<Dims...>(indices...);
}
 
template < typename T, size_t... Dims >
struct Array {
     
    template <typename... Indices>
    static size_t OffsetAt( Indices... indices ) {
        static_assert(sizeof...(Indices) == sizeof...(Dims), "noooooo" );
        return Index<Dims...>(indices...);
    }
     
    template <typename... Indices>
    T& operator() ( Indices... indices ) {
        return data_[ OffsetAt(indices...) ];
    }
     
private:
    std::unique_ptr<T[]> data_ { new T[Mul<Dims...>::value] };
};
 
int main() {
    Array<int,3,5,10> array;
    std::cout << array.OffsetAt(1,0,0) << std::endl;
    std::cout << array.OffsetAt(1,1,0) << std::endl;
    std::cout << array.OffsetAt(1,0,3) << std::endl;
}