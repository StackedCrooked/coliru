#include <iostream>
#include <iterator>
#include <numeric>
#include <string>

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    auto str = std::accumulate(std::begin(arr), std::end(arr), std::string(), [](const std::string &acc, int i) {
        return acc + std::to_string(i);
    });
    std::cout << str;
}