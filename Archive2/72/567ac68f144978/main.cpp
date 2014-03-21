#include <iostream>

template<int N, size_t P=0u> struct Log2 
    { enum { value = Log2<N/2,P+1>::value }; };

template <size_t p>
struct Log2<0, p> { enum { value = p }; };

template <size_t p>
struct Log2<1, p> { enum { value = p }; };

const char *p[] = { "abc", "efg" };

int main(int argc = 2, const char **argv = p)
{
    std::cout << argc << std::endl;
}
