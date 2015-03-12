#include <iostream>
#include <type_traits>
#include <tuple>

using namespace std;

struct X {
    X() : c(10), d(20) {} 
    int a() { return 0; }
    int b() { return 1; }
    int c;
    int d;
};

#define TYPEDEF_IS_MEMBER_FOO(CLS)   &CLS::a, &CLS::b
#define TYPEDEF_IS_MEMBER_FIELD(CLS) &CLS::c, &CLS::d

template<typename T, int i> 
using member_field_type = 
      tuple_element<i, decltype(make_tuple( TYPEDEF_IS_MEMBER_FIELD(T) ))>;

template<typename T, int i> 
typename member_field_type<T,i>::type member_field = 
         std::get<i>(std::make_tuple( TYPEDEF_IS_MEMBER_FIELD(T) ) ); 


int main() {

    cout << is_same<member_field_type<X,0>::type, decltype(&X::c)>::value << endl;
    member_field_type<X,0>::type first = member_field<X,0>;
    
    X x;
    cout << (x).*first << endl;
}