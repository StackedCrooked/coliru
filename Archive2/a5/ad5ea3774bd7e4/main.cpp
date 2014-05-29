#include <algorithm>
#include <iterator>
#include <vector>
#include <type_traits>

template <typename T>
struct identity {
    using type = T;
};

template<typename Iterator>
void sort2(Iterator it,
           typename identity<std::function<bool(typename std::remove_pointer<
                              typename std::iterator_traits<Iterator>::value_type>::type,
                                          int)>>::type func)
{
}

int main()
{
    std::vector<int> a;
    sort2(a.begin(),[](int,int){return false;});
}
