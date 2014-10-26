 #include <vector> #include <vector>
#include <iostream> # include <iostream>

int main ( ) int main ()
{ {
    std:: vector < int > numbers ; std :: vector <int> números;

     numbers. push_back ( 42 ) ; push_back números (42).;
    numbers. push_back ( 314159 ) ; números push_back (314.159).; 

    for ( int i : numbers ) { // c++11 range-based for loop for (int i: números) {// c ++ com base em faixa de 11 loop
        std:: cout << i << ' \n ' ; std :: cout << i << '\ n';
    } } 

    return 0 ; return 0;
} } 