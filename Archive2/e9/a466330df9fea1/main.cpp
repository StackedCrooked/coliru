#include <type_traits>
#include <array>
#include <iostream>

//-----------------------------------------------------------------------------

// using a list-initializer constructor, evaluate arguments in order of appearance
struct Do { template <typename... T> Do(T&&...) { } };

//-----------------------------------------------------------------------------

// holds a single size_t number
template<size_t N>
using size = std::integral_constant<size_t, N>;

// holds any number of size_t parameters
template <size_t... N>
struct sizes { using type = sizes <N...>; };

//-----------------------------------------------------------------------------

// given L>=0, generate sequence <0, ..., L-1>
template <size_t L, size_t I = 0, typename S = sizes <> >
struct Range;

template <size_t L, size_t I, size_t... N>
struct Range <L, I, sizes <N...> > : Range <L, I+1, sizes <N..., I> > { };

template <size_t L, size_t... N>
struct Range <L, L, sizes <N...> > : sizes <N...> { };

//-----------------------------------------------------------------------------

template<typename T>
constexpr T pack(bool b) { return b; }

template<typename T, typename... Types>
constexpr T pack(bool b, Types... args)
{
	return (b << sizeof...(Types)) | pack<T>(args...);
}

//-----------------------------------------------------------------------------

template<size_t N, size_t... I, typename T>
constexpr std::array<bool, N>
unpack(sizes<I...>, T packed)
{
	return std::array<bool, N>{{(packed & (1 << (N-I-1))) != 0 ...}};
}

template<size_t N, typename T>
constexpr std::array<bool, N>
unpack(T packed)
{
	return unpack<N>(typename Range<N>::type(), packed);
}

template<typename T, size_t N = 8*sizeof(T)>
constexpr std::array<bool, N>
unpack(T packed) { return unpack<N>(packed); }

//-----------------------------------------------------------------------------

template<typename S, typename T, size_t N>
S& operator<<(S& s, const std::array<T, N>& a)
{
	for (auto i : a)
		s << i << " ";
	return s;
}

//-----------------------------------------------------------------------------

int main(void)
{
    std::cout << pack<int>(1, 0, 0, 1, 0, 1, 1, 0) << std::endl; // 150
    std::cout << pack<int>(1, 0, 1) << std::endl; // 5
    int val = pack<int>(1, 0, 1);

	 // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1
	 std::cout << unpack(val) << std::endl;

	 // 0 0 0 0 0 1 0 1
	 std::cout << unpack<8>(val) << std::endl;
}