#include <cstring>
#include <vector>

int main()
{
    std::vector<char> v(100);
    
#ifdef USE_WRAP
    struct Wrap
    {
        Wrap() {}
        operator const char & () const { return c; }
        char c;
    };
    std::vector<char> copy(v.size(), Wrap());
#else
    std::vector<char> copy(v.size());
#endif


    std::memcpy(&copy[0], v.data(), v.size());
}