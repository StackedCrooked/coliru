#include <iostream>
#include <type_traits>
#include <string>
using namespace std;

template <typename T>
struct S
{
    S()
    {
        cout << "S<T>::S()" << endl;
    }
};

template <>
S<int>::S() = default;

int main()
{
    cout << "S<char>:" << endl;
    S<char> sc;
    cout << "S<int>:" << endl;
    S<int> si;
}
