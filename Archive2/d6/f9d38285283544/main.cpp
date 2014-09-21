#include <utility>
#include <iostream>

template <typename>
struct invoke_helper;

template <size_t... Is>
struct invoke_helper<std::index_sequence<Is...>>
{
    template <typename F, typename T>
    static void invoke(F command, T* array)
    {
        command(array[Is]...);
    }
};

template <size_t N, typename F, typename T>
void invoke(F command, T* array)
{
    invoke_helper<std::make_index_sequence<N>>::invoke(command, array);
}

template <typename F, typename T, size_t N>
void invoke(F command, T (&array)[N])
{
    invoke<N>(command, +array);
}

int main()
{
    auto command = [](int a, int b, int c) { std::cout << a << b << c; };
	int args[] = { 1, 2, 3 };
	invoke(command, args);
}