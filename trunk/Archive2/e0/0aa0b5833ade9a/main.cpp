#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <cassert>
#include <boost/container/stable_vector.hpp>

using namespace std;
template <typename T>
using ptr = typename std::add_pointer<T>::type;

int identity(int x)
{
    return x;   
}
int square(int x)
{
    return x*x;
}
int cube(int x)
{
    return x*x*x;
}
int main()
{
    std::vector<ptr<int (int)>> v; // vector of pointers to functions taking `int`
    v.push_back(&square);
    v.push_back(&cube);
    v.push_back(&identity);
    for(const auto& func: v)
        cout << func (26) << endl;
    cout << "bye" ;

}
