#include <iostream>
#include <vector>

using namespace std;

class Foo
{
public:
    Foo(int size, int value){} // create 'size' number of elements
    [[deprecated]]
    Foo(initializer_list<int> list){}  // create elements as in 'list'
};

int main()
{
    Foo foo{10, 2};
    
    
}