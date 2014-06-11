#include <tuple>
#include <iostream>
#include <typeinfo>

template <std::size_t N, typename...TYPES>
struct TupleElement;

template <typename FIRST, typename...REST>
struct TupleElement<0, std::tuple<FIRST, REST...>> {
    typedef FIRST type;
};

template <int N, typename FIRST, typename...REST>
struct TupleElement<N, std::tuple<FIRST, REST...>> {
    typedef typename TupleElement<N-1, std::tuple<REST...>>::type type;
};

int main() {
    std::tuple<int, char, double> myTuple = std::make_tuple(2, 'a', 3.14);
	TupleElement<2, decltype(myTuple)>::type d;
    
    std::cout << "The type is " <<  typeid(d).name() << '\n';
}