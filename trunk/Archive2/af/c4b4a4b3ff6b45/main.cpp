#include <vector>
using namespace std;
// Primary template:
template<typename T> struct Foo {};

// Partial specialization:
template<typename T> struct Foo< vector<T> > {};

// Explicit specialization:
template<> struct Foo< vector<int> > {};

int main ()
{
    Foo<vector<char>> x;
    Foo<vector<int>> y;
    Foo<char> z;
}