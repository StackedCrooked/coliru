#include <iostream>
#include <string>
#include <vector>

template <typename T>
struct X {
    static std::vector<int> __xs;
    static const std::vector<int>& get_xs()
    {
        return __xs;
    }
    
    std::vector<int> xs;
    X():xs(get_xs()) {}
};

int main()
{
    X<int> x;
}
