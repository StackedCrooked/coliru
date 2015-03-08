#include <iostream>
#include <vector>

int main()
{
    {
        // uniform initialisation (C++11): http://www.stroustrup.com/C++11FAQ.html#uniform-init
        const int a[] { 0, 1, 2, 3, 4 } ;
        const int N = sizeof(a) / sizeof( a[0] ) ; // size of array divided by size of an element

        const int b[N] { 0, 1, 2, 3, 4 } ;  // N is a constant known at compile-time:

        // compare arrays a and b for equality
        // compare element by element in sequence, in a loop
        bool equal_so_far = true ;
        for( int i = 0 ; ( i < N ) && equal_so_far ; ++i )
            if( a[i] != b[i] ) equal_so_far = false ;

        if( equal_so_far ) std::cout << "all elements compare equal\n" ;

        const int* pa = a ; // implicit conversion from array to pointer
        const int* pb = b ; // implicit conversion from array to pointer
        if( pa != pb )
            std::cout << "but pointers to the respective first elements do not compare equal\n" ;

        if( a != b ) // implicit conversion from array to pointer 
            std::cout << "but pointers to the respective first elements do not compare equal\n" ;
        // that ( a != b ) is known to be true at compile time (a and b are two different arrays); 
        // therefore, clang++ warns us about the tautology (did you seriously expect this to be not true?)   
    }

    std::cout << "--------------\n" ;

    {
        // initialiser list (C++11): http://www.stroustrup.com/C++11FAQ.html#init-list
        const std::vector<int> a { 0, 1, 2, 3, 4 } ;
        const std::vector<int> b = a ; // b is another vector which is a copy of a (copy initialisation)

        // use the overloaded operator== for vectors (provided by the library)
        // http://en.cppreference.com/w/cpp/container/vector/operator_cmp
        if( a == b ) std::cout << "all elements compare equal\n" ;

        if( &( a.front() ) != &( b.front() ) ) // also see std::addressof(): http://en.cppreference.com/w/cpp/memory/addressof
            std::cout << "but pointers to the respective first elements do not compare equal\n" ;
    }
}
