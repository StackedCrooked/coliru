#include <iostream>
#include <utility>

template <typename T, size_t N>
struct UninitializedArray
{
    UninitializedArray() {}
    using U = T(&&)[N];
    operator U() { return std::move(arr); }
    T arr[N];
};

template <typename T>
struct identity { using type = T; };

template <size_t szArr, typename typeArrs>
auto fnAdd2ArrayElements(const typeArrs (&arr_0)[szArr], const typeArrs (&arr_1)[szArr]
                       , typename identity<typeArrs(&&)[szArr]>::type result = UninitializedArray<typeArrs,szArr>{}) -> typeArrs (&&)[szArr]
{
    std::cout << result[0] << std::endl;
    
    for(size_t i(0); i < szArr; ++i)
        result[i] = arr_0[i] + arr_1[i];

    return std::move(result);
}

int main()
{
    int a[5] = { 1, 2, 3, 4, 5 };
    int b[5] = { 6, 7, 8, 9, 0 };    
    std::cout << fnAdd2ArrayElements(a, b)[0] << std::endl;
}
