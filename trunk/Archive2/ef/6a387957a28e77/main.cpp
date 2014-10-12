#include <vector>

template <typename T>
void sort(typename T::iterator begin, typename T::iterator end) {}

int main()
{
    std::vector<int> v;
    sort<std::vector<int>>(v.begin(), v.end());
}
