#include <array>
#include <iostream>
#include <type_traits>

template<int Base, int Exp>
struct Pow
{
	static const int value = Base * Pow<Base, Exp - 1>::value;
};

template<int Base>
struct Pow<Base, 0>
{
	static const int value = 1;
};

template<int A, int B>
struct NumCompare
{
	static const bool value = (A < B);
};

template<int N, template<int> class Sequence, class Enable = void>
struct MaxSequenceIndex
{
	static const int value = 0;
};

template<int N, template<int> class Sequence>
struct MaxSequenceIndex<N, Sequence, typename std::enable_if<NumCompare<0, Sequence<N>::value>::value>::type>
{
	static const int value = MaxSequenceIndex<N + 1, Sequence>::value;
};

template<int N, template<int> class Sequence>
struct MaxSequenceIndex<N, Sequence, typename std::enable_if<NumCompare<Sequence<N>::value, 0>::value>::type>
{
	static const int value = N - 1;
};

template<int... Idxs>
struct Indices {};

template<int N>
struct PowersOfThree
{
    static const int value = Pow<3, N>::value;
};

template<template<int> class Sequence = PowersOfThree, int N = MaxSequenceIndex<0, Sequence>::value, int... Idxs>
struct PowersOfThreeSeq : PowersOfThreeSeq<Sequence, N - 1, N - 1, Idxs...>
{
	static const std::array<int, N + 1> sequenceValues;
};

template<template<int> class Sequence = PowersOfThree, int N = MaxSequenceIndex<0, Sequence>::value, int... Idxs>
const std::array<int, N + 1> PowersOfThreeSeq<Sequence, N, Idxs...>::sequenceValues = { PowersOfThree<Idxs>::value... };

template<template<int> class Sequence, int... Idxs>
struct PowersOfThreeSeq<Sequence, 0, Idxs...> : Indices<Idxs...>
{
	static const std::array<int, 1> sequenceValues;
};

template<template<int> class Sequence, int... Idxs>
const std::array<int, 1> PowersOfThreeSeq<Sequence, 0, Idxs...>::sequenceValues = { Sequence<0>::value };

int main(int argc, char* argv[])
{
    auto x = PowersOfThreeSeq<>::sequenceValues;
	int idx = 0;
	for (auto i : x) { std::cout << idx++ << ": " << i << std::endl; }
    
	return 0;
}