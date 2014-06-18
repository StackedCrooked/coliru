#include <iostream>
#include <vector>

using namespace std;

template<class To, class From>
vector<To> ConvertSTDVector_AToB(vector<From> const& vector)
{
    return { vector.begin(), vector.end() };
}

int main() {
    for (auto i : ConvertSTDVector_AToB<int>(vector<char>{ 'a', 'b', 'c' })) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}