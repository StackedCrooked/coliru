#include <memory>

std::unique_ptr<int> a()
{
    std::unique_ptr<int> ptr(new int());
    return ptr;
}

std::unique_ptr<int> b()
{
    static std::unique_ptr<int> ptr(new int());
    return std::move(ptr);
}

int main()
{
}