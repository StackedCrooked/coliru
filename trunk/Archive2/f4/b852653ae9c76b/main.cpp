#include <algorithm>
#include <type_traits>

template<class Iter>
void reverse(Iter first, Iter last) {
    std::reverse(first, last);
}

template<typename T>
void reverse(T& x, typename std::enable_if<sizeof(T)==sizeof(uint32_t), void*>::type sfinae = nullptr)
{
    *reinterpret_cast<uint32_t*>(&x) = byteswap32(*reinterpret_cast<uint32_t*>(&x));
}
 
template<typename T>
void reverse(T& x, typename std::enable_if<sizeof(T)!=4, void*>::type sfinae = nullptr)
{
    auto f = reinterpret_cast<unsigned char*>(&x);
    auto l = f + sizeof(T);
    return reverse(f,l);
}
 
int main(int argc, char **argv) {
    uint32_t x = 0xdeadbeef;
    
    reverse(x);
    
    return 0;
}
