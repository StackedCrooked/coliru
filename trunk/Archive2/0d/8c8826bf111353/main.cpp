#include <type_traits>

using namespace std;

template<typename T, typename = void>
struct has_id : false_type { };

template<typename T>
struct has_id<T, decltype(declval<T>().id, void())> : true_type { };

#include <iostream>

using namespace std;

struct X { int id; };
struct Y { int foo; };

int main()
{
    cout << boolalpha;
    cout << has_id<X>::value << endl;
    cout << has_id<Y>::value << endl;
}