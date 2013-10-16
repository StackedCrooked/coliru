#include <iostream>
#include <functional>
#include <iterator>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
 
int is_odd(int n) { return n%2; }
int is_big(int n) { return n>5; }

bool is_odd_2(const int &n) { return n%2; }
bool is_big_2(const int &n) { return n>5; }

using namespace std;
using namespace std::placeholders;

template <typename T>
struct AND
{
    function<bool (const T&)> x;
    function<bool (const T&)> y;
    
    AND(function<bool (const T&)> xx, function<bool (const T&)> yy) : x(xx), y(yy) {}
    bool operator() ( const T &arg ) 
    {
        return x(arg) && y(arg);
    }
};

template <typename T>
AND<T> And(function<bool (const T&)> xx, function<bool (const T&)> yy)
{
    return AND<T>(xx,yy);
}

bool big_odd_exists( vector<int>::iterator first, vector<int>::iterator last ); // fwd decl

int main()
{
    std::vector<int> n = {1, 3, 5, 7, 9, 10, 11};

    cout << "exists : " << big_odd_exists( n.begin(), n.end() ) << endl;
    
    return 0;
}

/*
bool big_odd_exists( vector<int>::iterator first, vector<int>::iterator last ) 
{
    function<bool (const int &)> fun1 = is_odd;
    function<bool (const int &)> fun2 = is_big;

    return any_of( first, last, And( fun1, fun2 ) );
}
*/

/*
bool big_odd_exists( vector<int>::iterator first, vector<int>::iterator last ) 
{
    return any_of( first, last, And( is_odd, is_big ) );  // won't compile
}
*/

bool big_odd_exists( vector<int>::iterator first, vector<int>::iterator last ) 
{
    return any_of( first, last, And( is_odd_2, is_big_2 ) );  // won't compile
}
/*
bool big_odd_exists( vector<int>::iterator first, vector<int>::iterator last ) 
{
    function<bool (const int &)> fun1 = bind(is_odd,_1);
    function<bool (const int &)> fun2 = bind(is_big,_1);

    return any_of( first, last, And(fun1, fun2) );
}
*/
/*
bool big_odd_exists( vector<int>::iterator first, vector<int>::iterator last ) 
{
    return any_of( first, last, And(bind(is_odd,_1), bind(is_big,_1)) );  // won't compile
}
*/

