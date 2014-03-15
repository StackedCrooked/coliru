#include <iostream>

template<const int* arr>
struct array_container
{
    static constexpr int val = arr[0];
    array_container() {
        std::cout << val << std::endl;
    }
//  static constexpr int arr_size = ??;
};

constexpr int one[] = { 1 };
constexpr int two[] = { 1, 2 };

int main()
{
    array_container<one> array_one;
    array_container<two> array_two;
    (void) array_one;
    (void) array_two;
    return 0;
}