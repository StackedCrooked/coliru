#include <iostream>
#include <type_traits>
#include <memory>

template <typename T>
struct is_shared_ptr_impl : std::false_type {};
template <typename T>
struct is_shared_ptr_impl<std::shared_ptr<T>> : std::true_type {};
template <typename T>
using is_shared_ptr = typename is_shared_ptr_impl<typename std::decay<T>::type>::type;

class Foo
{
public:    
    template <typename T>
    auto bar()
        -> typename std::enable_if<!is_shared_ptr<T>{}, T>::type
    {
        std::cout << "T" << std::endl;
        return {};
    }
    
    template <typename T>
    auto bar()
        -> typename std::enable_if<is_shared_ptr<T>{}, T>::type
    {
        std::cout << "shared_ptr" << std::endl;
        return {};
    }
};

int main()
{
    Foo foo;
    foo.bar<int>();
    foo.bar<long>();
    foo.bar<std::shared_ptr<int>>();
    foo.bar<std::shared_ptr<long>>();
}
