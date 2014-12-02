#include <iostream>
#include <type_traits>
 
using namespace std;
 
struct FooNo {};
struct FooYes { int x; };
 
template <typename T, typename = int>
struct HasX : false_type { };
 
template <typename T>
struct HasX <T, decltype((void) T::x, 0)> : true_type { };
 
int main() {
    cout << HasX<FooYes>::value << endl;
    cout << HasX<FooNo>::value << endl;
}
