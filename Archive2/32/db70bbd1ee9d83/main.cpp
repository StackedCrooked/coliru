#include <functional>

int main()
{
    std::function<void ()> f = [&]() { f(); };
}
