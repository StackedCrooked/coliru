#include <iostream>

#define MY_CAT__(s, x) s ## x
#define MY_CAT_(s, x) MY_CAT__(s, x)
#define PREPEND_MACRO1(x) MY_CAT_(MACRO1, x)

void PREPEND_MACRO1(MACRO2)()
{std::cout << __PRETTY_FUNCTION__ << '\n';}

int main()
{
    PREPEND_MACRO1(MACRO2)();
}