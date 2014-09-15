#include <future>

int main()
{
    std::promise<int> p;
    p.swap(decltype(p)());
}