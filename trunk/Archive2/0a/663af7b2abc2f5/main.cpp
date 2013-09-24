#include <type_traits>

using namespace std;

template<typename Iterator, typename Function>
static inline auto call(Iterator it, Function function) -> decltype(function(it))
{
    return function(it);
}

int main()
{
    char buffer[] = { 0, 1, 2, 3 };
    call(&buffer[0], [](char*&) { });

    return 0;
}
