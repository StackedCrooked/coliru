#include <type_traits>
#include <iostream>

using namespace std;

template<typename Iterator, typename Function>
static inline auto take(Iterator& it, Function function) -> decltype(function(it))
{
    for ( ; ; ++it) {
        if (auto result = function(it))
            return result;
    }
}

int main()
{
    typedef char* iterator;
    typedef char value;

    value buffer[] = { 4, 3, 1, 2, 0, 7, 8 };
    auto it = &buffer[0];

    value minimum = 7;
    value result = take(it, [=](iterator& it) -> value {
        value result = *it;
        if (result < minimum)
            return 0;

        *it = 0;
        return result;
    });

    cout << "should be 7: " << static_cast<int>(result);
    
    return 0;
}
