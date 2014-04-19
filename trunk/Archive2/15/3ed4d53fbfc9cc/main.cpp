#include <iostream>
#include <type_traits>
using namespace std;

template<typename R, R V = R(), class = typename std::enable_if<!is_same<R, void>::value>::type> R X() { return V; }
template<typename R, class = typename std::enable_if<is_same<R, void>::value>::type> R X() { return; }

int main()
{
    cout << boolalpha << X<bool>() << endl;    
    cout << boolalpha << X<bool, true>() << endl;

    cout << X<int>() << endl;
    cout << X<int, 5>() << endl;

    X<void>();

    return 0;
}
