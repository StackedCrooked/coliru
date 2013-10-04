#include <iostream>
#include <type_traits>

using namespace std;

template<typename T, T N, T M, typename enable = void>
struct is_greater_than; // undefined

template<typename T, T N, T M>
struct is_greater_than<T, N, M, typename std::enable_if<std::is_integral<T>::value >::type>
{
    static const bool value = N > M;
};

int main()
{
    bool a = is_greater_than<int, 11, 10>::value;

    cout << a << endl;
}
