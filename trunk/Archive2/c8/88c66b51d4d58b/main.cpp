#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (const T& el : vec)
    {
        os << el << ' ';
    }
    os << endl;
    return os;
}

void FillVector1( vector<int>& vec )
{
    cout << "One version called\n";
    vec.clear();
    for( int x =0; x < 10; ++x )
    {
        vec.push_back( x );
    }
}

void FillVector2( vector<int>& vec )
{
    cout << "Two version called\n";
    vec.clear();
    for( int x =0; x < 10; ++x )
    {
        vec.insert( vec.end(), x );
    }
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "Roland", "!"
    };
    std::cout << words;
    
    vector<int> v1;
    FillVector1( v1 );
    cout << "v1: " << v1;

    vector<int> v2;
    FillVector2( v2 );
    cout << "v2: " << v2;
}
