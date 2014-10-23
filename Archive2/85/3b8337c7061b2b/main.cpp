template <template <typename T> class...>
struct my_class {};

template <typename T>
struct define_template
{
    template <typename U>
    class type {};
};

template <typename... T>
using new_class = my_class<define_template<T>::template type...>;

int main()
{
    new_class<int, char> m;
    (void)m;
}
