#include <functional>

void g() {}

int main()
{
    auto f = []() { g(); };
}
