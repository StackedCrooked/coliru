#include <iostream>
#include <list>
#include <algorithm>

int main() {
    std::list<int> integers = {1, 5, -6};
    std::sort(integers.begin(), integers.end());
}