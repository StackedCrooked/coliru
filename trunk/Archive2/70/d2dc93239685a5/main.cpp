#include <iostream>
#include <vector>

template <typename T, template<class...> class ContainerType>
typename ContainerType<T>::iterator 
    elementIteratorAt(ContainerType<T> container, size_t)
{
    return container.end();
}

int main()
{
    std::vector<int> v;
    elementIteratorAt(v, 0);
}
