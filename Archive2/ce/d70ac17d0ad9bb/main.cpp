#include <algorithm>
#include <iterator>
#include <type_traits>
#include <vector>
#include <utility>

template <typename Iterator>
using ValueType = typename std::iterator_traits<Iterator>::value_type;

template<typename Iterator, typename Function>
auto sort2(Iterator first, Iterator last, Function func) ->
  typename std::enable_if<
    std::is_convertible<decltype(func(std::declval<ValueType<Iterator>>(),
                                      std::declval<ValueType<Iterator>>())),
                        bool>::value
  >::type
{
    std::sort(first, last, func);
}

int main()
{
    std::vector<int> a{5,4,3,2,1,0};
    sort2(a.begin(), a.end(), [](int,int){return false;});
}
