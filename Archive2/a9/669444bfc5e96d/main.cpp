    // class-hierarchy.hpp
#include <iostream>

struct english {
    struct substantives {
        struct House;
        struct Horse;
    };
};

// Optionally; to avoid long qualified names.
using House = english::substantives::House;
using Horse = english::substantives::Horse;

template<typename WordTag>
struct WordTraits;

template<> struct WordTraits<House>
{ static constexpr char const* word = "House"; };

template<> struct WordTraits<Horse>
{ static constexpr char const* word = "Horse"; };

template<typename TagWord>
constexpr char const* getString()
{ return WordTraits<TagWord>::word; }

int main()
{
    std::cout << getString<Horse>() << std::endl;
    std::cout << getString<House>() << std::endl;
}