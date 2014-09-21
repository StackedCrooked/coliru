#include <utility>
#include <iostream>

template <typename F, typename T, size_t... Is>
static void invoke(F command, T* array, std::index_sequence<Is...>)
{
    command(array[Is]...);
}

template <size_t N, typename F, typename T>
void invoke(F command, T* array)
{
    invoke(command, array, std::make_index_sequence<N>{});
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