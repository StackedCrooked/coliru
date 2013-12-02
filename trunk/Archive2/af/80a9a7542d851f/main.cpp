
#include <type_traits>

template<typename T>
void f(T)
{
    static_assert(T(), "first requirement failed to meet.");

    static_assert(T::value, "second requirement failed to meet.");    

    T t = 10; //even this may generate error!
}

int main()
{
    f(std::false_type{});
}
