#include <vector>

typedef char yes;
typedef int no;

template<class T> struct has_value_type {
   template<class U> static yes test(typename U::value_type*);
    template<class U> static no  test(...);
    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

class C : private std::vector<int> {  };

int main() {
   return has_value_type<C>::value;
}