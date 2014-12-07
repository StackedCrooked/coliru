#include <functional>

void f(std::function<void()> const&){}

int main()
{
    f(0);
    f(NULL);
}