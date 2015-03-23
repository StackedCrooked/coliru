#include <memory>
#include <iostream>
#include <map>
#include <initializer_list>

std::shared_ptr<int> foo(std::initializer_list<std::pair<std::string, std::shared_ptr<int> > > il);
std::shared_ptr<int> foo(std::initializer_list<std::shared_ptr<int> > il);

std::shared_ptr<int> foo(int num);

int main()
{
    foo({ { "a", foo(10) } });
}