#include <type_traits>

using namespace std;

template<class Function>
static inline auto call(Function function) -> typename std::result_of<Function>
{
    return function();
}

int main()
{
    char a[] = { 1, 2, 3 };
    call([]() { });

    return 0;
}
