#include <initializer_list>

template<typename T, typename U, std::size_t N>
void set_elems(T (&arr)[N], std::initializer_list<std::size_t> idx, const U& val)
{
    for (std::size_t i : idx)
        arr[i] = val;
}

int main()
{
    int array[30];
    set_elems(array, {9,5,14}, 1);
}
