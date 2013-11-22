#include <iostream>

template<typename T> int compare( T&, T& )
{ std::cout << "template\n" ; return 0 ; }

int compare( const char*, const char* )
{ std::cout << "non-template overload\n" ; return 0 ; }

template<typename T> int compare2( const T&, const T& )
{ std::cout << "template const\n" ; return 0 ; }

int compare2( const char*, const char* )
{ std::cout << "non-template overload\n" ; return 0 ; }

int main()
{
    char ch_arr1[6] = "world", ch_arr2[6] = "hello" ;

    compare( ch_arr1, ch_arr2 ) ; // template; T decuced to be char[6]
    compare2( ch_arr1, ch_arr2 ) ; // template const; T decuced to be char[6]

    compare( ch_arr1, +ch_arr2 ) ; // non-template overload
    compare2( ch_arr1, +ch_arr2 ) ; // non-template overload

    char ch_arr3[7] = "hello";

    compare( ch_arr1, ch_arr3 ) ; // non-template overload
    compare2( ch_arr1, ch_arr3 ) ; // non-template overload

    const char ch_arr4[6] = "world" ;

    compare( ch_arr1, ch_arr4 ) ; // non-template overload
    compare2( ch_arr1, ch_arr4 ) ; // // template const; T decuced to be char[6]
}
