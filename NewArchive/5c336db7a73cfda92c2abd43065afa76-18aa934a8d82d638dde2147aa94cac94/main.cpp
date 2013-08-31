#include <iostream>
#include <type_traits>

template<typename T, bool IsFunction = std::is_function<T>::value>
struct is_callable;

template<typename T>
struct is_callable<T, true>
{
    static const bool value = true;
};

template<typename T>
struct is_callable<T, false>
{
    private:

        using yes   = uint8_t;
        using no    = uint16_t;

        struct basemixin
        {
            void operator()() {}
        };

        struct Base:
            public T,
            public basemixin
        {};

        template <typename U, U>
        class helper {};

        template <typename U>
        static no deduce(U*, helper<void (basemixin::*)(), &U::operator()>* = 0);

        static yes deduce(...);

    public:

        static const bool value = sizeof(yes) == sizeof(deduce((Base*)(0)));
};
void a() {}

int main()
{
    std::cout << std::is_function<decltype(a)>::value << std::endl; // prints true
    std::cout << is_callable<decltype(a)>::value << std::endl;

    return 0;
}