#include <string>
#include <iostream>
template<typename TChar, size_t TSize>
inline size_t StringLength(TChar(&)[TSize])
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return TSize - 1;
}

template<typename TChar>
inline size_t StringLength(const TChar* const & value)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return std::char_traits<TChar>::length(value);
}

int main() {
    const char * p = "def";
    char q[10] = "";
    const char w[10] = "foobar";
    char *  x = q;
    
    std::cout << "Should be array version:" << std::endl;
    StringLength("abc");
    StringLength(q);
    StringLength(w);
    
    std::cout << "Should be pointer version:" << std::endl;
    StringLength(p);
    StringLength(x);
}