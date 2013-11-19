#include <map>
#include <vector>
#include <list>
#include <unordered_map>
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;
using namespace std::placeholders;


bool is_odd(int n) {
    return n%2 != 0;
}

void add_if_number_is_odd( int n, int *sum ) {
    if( is_odd(n) )  {
        *sum += n;
    }
}

int main()
{
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int sz = sizeof(arr)/sizeof(int);


    // change the following code to get the same result:
    // from here ....
    
    int total = 0;
    for( int i=0; i<sz; i++ )
    {
        add_if_number_is_odd( arr[i], &total );
    }

    // ... to here


    cout << "total is " << total;
}