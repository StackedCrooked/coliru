#include <algorithm>
#include <iostream>

int main() {
    int arr[2][2] = {{434, 43}, {9826, 2}};
    auto min_ptr = std::min_element(&arr[0][0], &arr[0][0] + 4);
    auto max_ptr = std::max_element(&arr[0][0], &arr[0][0] + 4);
    std::cout << *min_ptr << "/" << *max_ptr;
}