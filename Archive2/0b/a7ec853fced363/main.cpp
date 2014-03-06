#include <vector>
#include <iostream>

using namespace std;

vector<int> doubleValues (const vector<int>& v)
{
    vector<int> new_values;
    new_values.reserve();
    for (auto itr = v.begin(), end_itr = v.end(); itr != end_itr; ++itr )
    {
        new_values.push_back( 2 * *itr );
    }
    return new_values;
}

int main()
{
    vector<int> v;
    for ( int i = 0; i < 100; i++ )
    {
        v.push_back( i );
    }
    v = doubleValues( v );
}