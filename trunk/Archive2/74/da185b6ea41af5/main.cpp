template <int...> struct IndexSequence {};

template <int, int, typename, int...> struct Helper;

template <int Start, int... As, int... Is>
struct Helper<Start, Start, IndexSequence<As...>, Is...> {
    using type = IndexSequence<Is...>;
};

template <int Start, int N, int... As, int... Is>
struct Helper<Start, N, IndexSequence<As...>, Is...> :
    Helper<Start, N-1, IndexSequence<As...>, N-1, Is...> {};

#include <iostream>

template <typename TYPE>
void printType()
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
}

int main() {
    printType<   Helper<2,5, IndexSequence<1,2,3>>::type   >();
}