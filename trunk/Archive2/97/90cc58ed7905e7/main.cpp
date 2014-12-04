#include <iostream>
using namespace std;

template<typename... Args>
void func(Args... args, int optional = 0)
{
    cout << optional << endl;
}

int main()
{
    func(1);
    func(2.1f); // converts 2.1 to int as 'optional' parameter
    func<float>(3.3f);  // Fine, prints '0'
    func();  // gcc OK, fails to compile with clang-3.5
}
