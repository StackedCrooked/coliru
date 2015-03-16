#include <iostream>
#include <vector>
#include <set>

template <template<typename...> class OutputContainerType, template<typename...> class ContainerType, typename ValueType>
static OutputContainerType<ValueType> processContainer(ContainerType<ValueType> c)
{
    OutputContainerType<ValueType> result(c.begin(), c.end());
    return result;
}

int main() {
    std::set<int> s {1, 2, 3};
    auto v = processContainer<std::vector, std::set, int>(s);
    std::cout << v.size() << std::endl;
}