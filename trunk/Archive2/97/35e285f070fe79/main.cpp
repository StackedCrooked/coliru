#include <algorithm>
#include <vector>
#include <iterator>

template<typename Iterator>
void sort2(Iterator it,
           std::function<bool(typename std::iterator_traits<Iterator>::value_type, int)> func)
{
}

int main()
{
    std::vector<int> a;
    sort2(a.begin(),std::function<bool(int, int)>([](int,int){return false;}));
}
