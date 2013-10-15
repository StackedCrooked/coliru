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

template <typename X, typename Y>
struct AND
{
    X x;
    Y y;
    
    AND(X xx, Y yy) : x(xx), y(yy) {}
    bool operator() ( const typename X::argument_type &arg ) 
    {
        return x(arg) && y(arg);
    }
};

template <typename X, typename Y>
AND<X,Y> my_and(X xx, Y yy)
{
    return AND<X,Y>(xx,yy);
}

int main()
{
    std::vector<int> n = {1, 3, 5, 7, 9, 10, 11};

    auto it = find_if( n.begin(), n.end(), my_and( ptr_fun(is_odd), ptr_fun(is_big) ) );
    if( it != n.end() ) {
        cout << *it << endl;
    }
}