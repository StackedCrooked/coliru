#include <boost/heap/fibonacci_heap.hpp>
#include <iostream>

using namespace boost;
using namespace std;

typedef heap::fibonacci_heap<int>::handle_type handle;
struct WithBool
{
    handle h;
    bool was_set;
};
struct WithoutBool
{
    handle h;
};

int main()
{
    cout << sizeof(WithBool) << endl;
    cout << sizeof(WithoutBool) << endl;
}