#include <functional>
#include <iostream>
#include <type_traits>
#include <tuple>

using namespace std;

struct X {
    X() : c(10), d(20) {} 
    double a() { return 100; }
    double b() { return 200; }
    int c;
    int d;
};

#define TYPEDEF_IS_MEMBER_FOO(CLS)      &CLS::a, &CLS::b
#define TYPEDEF_IS_MEMBER_FIELD(CLS)    &CLS::c, &CLS::d
#define TYPEDEF_IS_MEMBER_FIELD_NM      "c", "d"

template<typename T, int i> 
using member_field_type = 
      tuple_element<i, decltype(make_tuple( TYPEDEF_IS_MEMBER_FIELD(T) ))>;

template<typename T, int i> 
typename member_field_type<T,i>::type member_field = 
         std::get<i>(std::make_tuple( TYPEDEF_IS_MEMBER_FIELD(T) ) ); 

template<typename T, int i> 
const char* member_field_nm
        = std::get<i>(std::make_tuple( TYPEDEF_IS_MEMBER_FIELD_NM ) );


int main() {

    cout << is_same<member_field_type<X,0>::type, decltype(&X::c)>::value << endl;
    member_field_type<X,0>::type first = member_field<X,0>;
    
    X x;
    cout << (x).*first << endl;
    
    cout << member_field_nm<X,0> << endl << endl;
    
    cout << "get all member names" << endl;
    //for(auto &fields : {typename<T requires is_member_object_pointer>...}) {
    for(auto &field_name : {TYPEDEF_IS_MEMBER_FIELD_NM}) {
       cout << field_name << endl;
    }
    
    cout << endl << "run all functions" << endl;
    //for(auto &foos : {typename<T requires is_member_function_pointer>...}) {
    for(auto &foo : { TYPEDEF_IS_MEMBER_FOO(X) }) {
       cout << (x.*foo)() << endl;
    }
    
}