#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
using namespace std;


struct Position {
    int a,b,c,d,e;
    Position():a(-1),b(-1),c(-1),d(-1),e(-1){}
    Position(int a,int b,int c,int d,int e):a(a),b(b),c(c),d(d),e(e)
    {}
};

int main()
{
    int i=12, j=34, someValue=123;
    
    std::multimap<int,Position> countries;
    countries.emplace(std::piecewise_construct,
        std::forward_as_tuple(someValue),
        std::forward_as_tuple(i,j,-1,-1,-1));

    
    const auto &a = countries.find(someValue)->second;
    cout << a.a << " " << a.b << " " << a.c << " " << a.d << " " << a.e << endl;
}
