#include <type_traits>

template<int N>
struct Knuth
{
	static const int value = 3 * Knuth<N - 1>::value + 1;
};

template<>
struct Knuth<0>
{
	static const int value = 1;
};

template<int A, int B>
struct NumCompare
{
    static const bool value = (A < B);
};

// A is enabled via a template parameter
template<int N, template<int> class Sequence, class Enable = void>
class A; // undefined

template<int N, template<int> class Sequence>
class A<N, Sequence, typename std::enable_if<NumCompare<0, Sequence<N>::value>::value>::type>
{

};

int main()
{
    A<1, Knuth> aaa;
    
    return 0;
}