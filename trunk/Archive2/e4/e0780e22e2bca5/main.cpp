#include <functional>

void f(){}

using type = typename std::function<decltype(f)>::result_type;

int main()
{
}
