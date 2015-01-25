#include <algorithm> 

namespace test_helpers {

    template <typename T> 
        T& clone_to(T const& s, T& t) 
    { 
        return (t = s); 
    }

    template <typename T, std::size_t N> 
        auto clone_to(T const (&s)[N], T (&t)[N]) -> decltype(t)& 
    {
        std::copy(s, s+N, t);
        return t;
    }
}

#include <vector>
#include <cassert>

int main()
{
    using namespace test_helpers;
    {
        std::vector<int> a(10, 11), b;
        clone_to(a, b);
        assert(a == b);
    }

    {
        int a[10] = {11,11,11,11,11,11,11,11,11,11};
        int b[10];
        clone_to(a, b);
        assert(a != b);
        // boost::range::equal would do the trick here, not gonna copy it out
    }
}
