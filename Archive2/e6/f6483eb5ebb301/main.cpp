#include <type_traits>

class Type1 {};
class Type2 {};
class Type3 {};
class Type4 {};

class TypeZ {};

template<typename T>
struct Common_helper { using type = std::conditional<std::is_same<T, Type1>() || std::is_same<T, Type2>() || std::is_same<T, Type3>(), T, TypeZ>; };

template<typename T>
using Common = typename Common_helper<T>::type;

int main(){}