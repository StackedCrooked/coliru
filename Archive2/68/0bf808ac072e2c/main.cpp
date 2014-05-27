#include <iostream>
#include <typeinfo>
#include <type_traits>

using namespace std;

//  Unspecialized version
template<typename...Ts> struct Tmin;

template<typename T> struct Tmin<T> 
{using type = T;};

template<typename T1, typename...Ts>
struct Tmin<T1, Ts...>
{
private: using other = typename Tmin<Ts...>::type;
public:  using type = typename std::conditional<sizeof(T1) < sizeof(other), T1, other>::type;
};

int main()
{
    cout << typeid(Tmin<float, int, double>::type).name() << endl;
    return 0;
}