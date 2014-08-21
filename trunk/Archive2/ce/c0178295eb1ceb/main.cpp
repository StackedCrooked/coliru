#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> v;
    std::transform(v.begin(), v.end(), v.begin(), v.begin(), 
        static_cast<int const&(*)(int const&, int const&)>(std::max<int>));
}
