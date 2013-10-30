#include <algorithm>
#include <vector>
#include <iostream>
 
struct S
{
    int number;
    char name;
 
    S ( int number, char name  )
        : number ( number ), name ( name )
    {}
 
    // only the number is relevant with this comparison
    bool operator< ( const S& s ) const
    {
        return number < s.number;
    }
};
 
 
int main()
{
    // note: not ordered, only partitioned w.r.t. S defined below
    std::vector<S> vec = { {1,'A'}, {2,'B'}, {2,'C'}, {2,'D'}, {4,'G'}, {3,'F'} };
 
    S value ( 2, '?' );
 
    auto p = std::equal_range(vec.begin(),vec.end(),value);
 
    for ( auto i = p.first; i != p.second; ++i )
        std::cout << i->name << ' ';
}