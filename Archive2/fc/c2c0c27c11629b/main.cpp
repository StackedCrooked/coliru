#include <memory>
#include <vector>

class A {};

class B : public A {};

class C : public A {};

void foo(std::unique_ptr<A>&& a)
{
    std::vector<std::unique_ptr<A>> v;
    v.emplace_back(std::move(a));
}

int main()
{
    foo(std::make_unique<B>());
    return 0;    
}