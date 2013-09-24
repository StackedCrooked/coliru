#include <type_traits>

using namespace std;

template<typename Iterator, typename Function>
static inline auto take(Iterator& it, Iterator& end, Function function) -> decltype(function(it))
{
    for ( ; it != end; ++it) {
        if (auto result = function(it))
            return result;
    }
    
    return decltype(function(it))();
}

int main()
{
    
    return 0;
}
