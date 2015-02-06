#include <iostream>
#include <numeric>
#include <iterator>
#include <ctime>
#include <random>
#include <algorithm>

unsigned evensToRight_fun2code_original( int a[], unsigned sz )
{
    unsigned left = 0, right = sz-1;
    while( left < right )
    {
        //find first even
        while( left<right && a[left]%2 != 0 ) ++left;
        // find last odd
        while( left<right && a[right]%2 == 0 ) --right;

        if( left<right )// swap the elements
        {
            int temp = a[left];
            a[left] = a[right];
            a[right] = temp;
        }
    }
    return left;
}

void evensToRight_disch_improvement( int a[], int size )
{
    int left = 0;
    int right = size-1;

    while(left < right)
    {
        if( a[left]%2 )  // odd
        {
            ++left;
        }
        else  // even
        {
            int t = a[right];
            a[right] = a[left];
            a[left] = t;
            --right;
        }
    }
}

void test( const int test_data[], int array[], int N, const char* desc )
{
    std::cout << '\n' << desc << "\n-------------\n" ;

    std::copy( test_data, test_data+N, array ) ;
    auto start = std::clock() ;
    evensToRight_fun2code_original( array, N ) ;
    auto end = std::clock() ;
    std::cout << "  evensToRight_fun2code_original: " << (end-start) * 1000.0 / CLOCKS_PER_SEC << " msecs.\n" ;

    std::copy( test_data, test_data+N, array ) ;
    start = std::clock() ;
    evensToRight_disch_improvement( array, N ) ;
    end = std::clock() ;
    std::cout << "  evensToRight_disch_improvement: " << (end-start) * 1000.0 / CLOCKS_PER_SEC << " msecs.\n" ;
}

int main()
{
    const int N = 1024*1024*32 ;
    static int test_data[N] ;
    std::iota( std::begin(test_data), std::end(test_data), 0 ) ;
    static int array[N];
    for( int& v : array ) v = 1 ; // pull it into cache

    std::mt19937 rng( std::random_device{}() ) ;
    std::shuffle( std::begin(test_data), std::end(test_data), rng ) ;
    test( test_data, array, N, "random" ) ;

    for( int& v : test_data ) v *= 2 ;
    test( test_data, array, N, "only even" ) ;

    for( int& v : test_data ) { v *= 2 ; v += 1 ; }
    test( test_data, array, N, "only odd" ) ;
}
