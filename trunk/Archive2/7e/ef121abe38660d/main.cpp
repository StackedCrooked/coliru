#include <algorithm>
#include <iostream>

int main() {
    int arr[2][2] = {{434, 43}, {9826, 2}};
    auto pair = std::minmax_element(&arr[0][0], &arr[0][0] + 4);
    std::cout << *pair.first << "/" << *pair.second;
}