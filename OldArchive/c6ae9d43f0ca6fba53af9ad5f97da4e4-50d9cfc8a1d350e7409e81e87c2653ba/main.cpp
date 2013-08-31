#include <functional>

int main()
{
    std::bind([](int&&) {}, 0)();
}