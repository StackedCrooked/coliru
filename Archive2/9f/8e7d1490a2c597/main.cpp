// class-hierarchy.hpp
#ifndef CLASS_HIERARCHY_HPP
#define CLASS_HIERARCHY_HPP

#define WORD(x, y) \
   using y = x; \
   template<> struct WordTraits<y> { \
     static constexpr const char* word = #y; \
   }

struct english {
    struct substantives {
       struct House;
       struct Horse;
    };
};

template<typename WordTag>
struct WordTraits;

WORD(english::substantives::House, House);
WORD(english::substantives::Horse, Horse);

template<typename TagWord>
constexpr char const* getString()
{ return WordTraits<TagWord>::word; }

#endif // CLASS_HIERARCHY_HPP

// main.cpp
#include <iostream>
// #include "class-hierarchy.hpp"

int main()
{
    std::cout << getString<Horse>() << std::endl;
    std::cout << getString<House>() << std::endl;
}