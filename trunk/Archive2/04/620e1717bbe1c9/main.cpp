#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

template< typename T, typename... A >
struct create_functor
{
    struct functor
    {
        T operator()( A... arguments )
        {
            return function( arguments );
        }
    };
};

bool less_than( const int& a, const int& b )
{
    return a < b;
}

create_functor< bool, const int&, const int& >::functor< &less_than > less_than_int;

//auto less_than_int_a = std::function< bool(int,int) >( less_than ); 

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