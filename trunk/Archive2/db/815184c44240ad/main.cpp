#include <algorithm>
#include <functional>
#include <iostream>

int main() {
    int data[2] = {2, 1};
    std::less<int> l;
    std::sort(data+0, data+2, std::ref(l));
    std::cout << data[1];
}