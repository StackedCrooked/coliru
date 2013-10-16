#include <iostream>
#include <functional>
#include <iterator>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
 
int is_odd(int n) { return n%2; }
int is_big(int n) { return n>5; }



using namespace std;
using namespace std::placeholders;

typedef std::function<bool (const int &)> CbType;

void print( vector<CbType> funcs, const vector<int> &data )
{
    int ifun = 0;
    for( auto f : funcs  ) {
        cout << "f = " << ifun << endl;
        for( auto number : data )
            cout << "n = " << number << ":" << f(number) << endl;
        ifun++;
    }
}

int main()
{
    std::vector<int> n = {1, 3, 5, 7, 9, 10, 11};

    
    vector<CbType> funcs;
    
    funcs.push_back( is_odd );
    funcs.push_back( is_big );
    funcs.push_back( bind(logical_and<bool>(), bind(is_odd,_1), bind(is_big,_1) ) );
    
    print( funcs, n );
    
    vector<CbType> funcs2;
    funcs2.push_back( bind(logical_or<bool>(), bind(is_odd, _1), bind(is_big,_1)) );
    copy(funcs.begin(), funcs.end(), back_inserter(funcs2));
 

    print( funcs2, n );

    return 0;
}

