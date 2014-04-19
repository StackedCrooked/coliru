#include <iostream>
#include <type_traits>
using namespace std;
    
template<typename R, R V = R()>
typename std::enable_if<!is_same<R, void>::value, R>::type X() { return V; }

template<typename R>
typename std::enable_if<is_same<R, void>::value, R>::type X() { return; }
    
int main()
{
    cout << boolalpha << X<bool>() << endl;    
    cout << boolalpha << X<bool, true>() << endl;

    cout << X<int>() << endl;
    cout << X<int, 5>() << endl;

    X<void>(); // You can't print `void` with standard iostreams...

    return 0;
}