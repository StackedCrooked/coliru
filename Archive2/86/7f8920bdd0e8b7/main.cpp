#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
struct Wrapper {
    typedef T value_type;
};

int main()
{
    Wrapper<int>::value_type x = 5.8;
    cout << 5.8;
}
