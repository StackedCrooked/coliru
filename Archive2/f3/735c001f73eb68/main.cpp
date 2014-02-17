#include <iostream>
#include <vector>

using namespace std;

int main() {
    std::vector<int> v{1,2,3};
    std::cout << v.capacity() << ' ';
    v.resize(0);
    std::cout << v.capacity() << '\n';
}