#include <iostream>
#include <utility>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

#define ARRAYSIZE(array) sizeof(array) / sizeof(*array)
#define bogosort(array) bogosort_impl(array, ARRAYSIZE(array))

template <typename T>
void bogosort_impl(T array, size_t size)
{
    while (!std::is_sorted(array, array + size))
        std::random_shuffle(array, array + size);
}

int main()
{
    srand(time(nullptr));
    int num[] = {35, 54, 1, 4, 96, -2};
    bogosort(num);

    for (int n : num)
        cout << n << ", ";
}
