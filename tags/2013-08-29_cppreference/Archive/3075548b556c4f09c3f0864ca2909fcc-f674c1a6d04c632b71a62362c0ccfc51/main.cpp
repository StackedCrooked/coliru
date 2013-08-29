#include <vector>
#include <list>
#include <functional>
#include <type_traits>
#include <utility>

template <template<class> class ResultC, class SourceC, class Functionoid>
auto myMap(const SourceC &input, Functionoid f) -> ResultC<typename std::remove_reference<decltype(f(*std::begin(input)))>::type
{
    return {};
}
            
            
int main() {
    std::vector<char> input{'a', 1};
    std::list<int> result = myMap<std::list>(input, [](char i)->int{return i;});
}