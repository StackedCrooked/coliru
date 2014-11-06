#include <iostream>
#include <typeinfo>

template<typename T, char const *name_>
struct named {
    typedef T type;
    static constexpr const char *name = name_;
};

template< typename T >
struct extract_type
{ using type = T; };

template< typename T, const char* S >
struct extract_type< named< T, S > >
{ using type = T; };

template< typename T >
struct extract_name
{ static constexpr const char* value = ""; };

template< typename T, const char* S >
struct extract_name< named< T, S > >
{ static constexpr const char* value = S; };

template<typename T>
void foo() {
    std::cout << "type: " << typeid(typename extract_type<T>::type).name() <<
                 ", name: " << extract_name<T>::value << std::endl;
}

constexpr const char bar[] = "bar";

int main() {
    foo<int>();               // type: int, name:
    foo<named<int, bar>>(); // type: int, name: bar
}
