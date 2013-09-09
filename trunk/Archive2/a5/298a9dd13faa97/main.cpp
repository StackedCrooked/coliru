#include <list>
#include <deque>
#include <memory>

template <template <typename...> 
          class ContainerBase = std::list>
class MyClass 
{
    class Internal{};
    typedef ContainerBase<Internal*> Container;
};

int main()
{
    MyClass<std::deque> m;
}