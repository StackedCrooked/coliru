#include <memory>
#include <iostream>
#include <map>
#include <initializer_list>

std::shared_ptr<int> foo(const std::initializer_list<std::pair<const std::string, std::shared_ptr<int> > >& il)
{
    return std::make_shared<int>();
}
std::shared_ptr<int> foo(const std::initializer_list<std::shared_ptr<int> > & il)
{
    return std::make_shared<int>();
}

std::shared_ptr<int> foo(int num)
{
    return std::make_shared<int>();
}

int main()
{
    foo({ { "a", foo(10) } });
}