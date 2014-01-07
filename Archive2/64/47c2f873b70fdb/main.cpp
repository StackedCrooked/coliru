#include <iostream>
#include <array>
#include <cstdint>

// crude C++14'ish integer_sequence. 
// Better one is at http://stackoverflow.com/a/17426611/273767
// Even better one will be in your #include <utility> some day
template<int ...> struct seq { };
template<int N, int ...S> struct gens : gens<N-1, N-1, S...> { };
template<int ...S> struct gens<0, S...> { typedef seq<S...> type; };

// given position in the 1D representation of an X*Y matrix,
// return the value to put in that cell
template<std::uint32_t X, std::uint32_t Y>
constexpr int get_element(int pos)
{
    return pos % Y == pos / Y; // 1 if row == col, 0 otherwise
}

// build the 1D representation of the matrix
template <typename T, std::uint32_t X, std::uint32_t Y, int ...S>
constexpr std::array<T, X*Y> get_identity_array(seq<S...>) {
    return std::array<T, X*Y>{{get_element<X,Y>(S)...}};
}

// little constexpr tag type to select the right constructor
struct identity_t { constexpr identity_t() {} };
constexpr identity_t identity_tag;

template<typename T, std::uint32_t X, std::uint32_t Y>
class Matrix
{
    std::array<T, X*Y> data;
 public:
    // default ctor, zeroes out the matrix
    constexpr Matrix() : data() {}

    // identity matrix constructor
    constexpr Matrix(identity_t) : data(get_identity_array<T,X,Y>( typename gens<X*Y>::type() )) {}

    T& operator()(std::uint32_t row, std::uint32_t col) { return data[row*Y + col]; }
    constexpr T operator()(std::uint32_t row, std::uint32_t col) const { return data[row*Y + col]; }
};

int main()
{
     constexpr Matrix<int, 5, 5> m(identity_tag);

     std::array<int, m(0,0)> a; // test constexpr-ness

     for(int row = 0; row < 5; ++row)
     {
         for(int col = 0; col < 5; ++col)
             std::cout << m(row, col) << ' ';
         std::cout << '\n';
     }
}
