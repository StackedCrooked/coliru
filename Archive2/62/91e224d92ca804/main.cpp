#include <cstdio>

struct foo
{
};

template <typename T>
T& AsRef(T& arg)
{
    return arg;
}

template <typename T>
T* AsPtr(T& arg)
{
    return &arg;
}

template <typename T>
const T& AsCRef(T& arg)
{
    return arg;
}

template <typename T>
const T* AsCPtr(T& arg)
{
    return &arg;
}

template <class A, class B, class C, class D, class E, class F, class G, class H>
void eatWarnings(A, B, C, D, E, F, G, H)
{
}

int main(int, char**)
{
    foo   i;

    auto  fromRef     = AsRef(i);  // foo
    // reference gets stripped unless explicitly specified
    auto& refFromRef  = AsRef(i);  // foo&
    auto  fromPtr     = AsPtr(i);  // foo*

    auto  fromCRef    = AsCRef(i); // foo
    // reference gets stripped unless explicitly specified
    auto& refFromCRef = AsCRef(i); // const foo&
    auto  fromCPtr    = AsCPtr(i); // const foo*

    // right-most const after a reference or pointer always gets stripped
    const foo* const* const* const pppi = NULL; 
    auto apppi = pppi; // const foo* const* const*

    eatWarnings(fromRef, refFromRef, fromPtr, fromCRef, refFromCRef, fromCPtr, pppi, apppi);
    return 0;
}
