#include <functional>

int main()
{
    int i;
    std::function<void(int&)> f;
    std::function<void()> f2 = std::bind(f, std::ref(i));
}
