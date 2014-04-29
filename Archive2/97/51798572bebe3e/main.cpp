#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

template<typename T, typename U >
struct create_functor
{
    template < typename T (*function)( const U& u1, const U& u2 ) >
    struct functor
    {
        T operator()( const U& first, const U& second )
        {
            return function( first, second );
        }
    };
};


bool less_than( const int& a, const int& b )
{
    return a < b;
}

create_functor< bool, int, int >::functor< &less_than > less_than_int;

int main()
{
    vector<int> sample;
    sample.push_back( 1 );
    sample.push_back( 0 );
    sample.push_back( 3 );
    sample.push_back( -1 );
    sample.push_back( -5 );

    sort( sample.begin(), sample.end(), less_than_int );

    for( int a : sample )
    {
        cout << a << " ";
    }

    cout << endl;

    return 0;
}