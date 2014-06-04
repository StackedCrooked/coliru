#include <algorithm>
#include <vector>
#include <type_traits>

template<typename Iterator>
void sort2(Iterator it,
           std::function<bool(typename std::remove_pointer<
                              typename Iterator::value_type>::type,
                                          int)> func)
{
}

int main()
{
    std::vector<int> a;
    sort2(a.begin(),[](int,int){return false;});
}
