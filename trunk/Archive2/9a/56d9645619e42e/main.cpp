#include <iostream>
#include <typeinfo>
#include <type_traits>

using namespace std;

struct Grandma {};
struct Mom : Grandma {};
struct Son : Mom {};
struct Grandchild : Son {};

template<typename...Ts>
using LCA = typename std::remove_pointer<typename std::common_type<typename std::add_pointer<Ts>::type...>::type>::type;

int main()
    {
    LCA<Son, Grandchild, Son> obj1;
    LCA<Son, Grandchild, Mom, Son> obj2;
    LCA<Mom, Mom, Mom> obj3;
     
    cout << "obj1 type = " << typeid(obj1).name() << endl;
    cout << "obj2 type = " << typeid(obj2).name() << endl;
    cout << "obj3 type = " << typeid(obj3).name() << endl;
     
    return 0;
}
    