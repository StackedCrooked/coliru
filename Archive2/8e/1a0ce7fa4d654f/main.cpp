#include <list>
#include <memory>

template <template <typename, typename> 
          class Container = std::list>
class MyClass 
{
    class Internal
    { };

    Container<Internal*, std::allocator<Internal*>> my_list;
};

int main()
{
    MyClass<> m;
}