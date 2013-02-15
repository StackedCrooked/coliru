#include <fstream>
#include <iostream>
using namespace std;

class Object
{
private:
    Object( Object const& );
    Object( Object&& );
public:
    void doSomething() const {}
    Object( int );
    Object( int, int, int );
};

int main( int argc, char* argv[] )
{
    int p1 = 0, p2 = 0, p3 = 0;
    bool condition = argc == 2;
    auto const doSomethingTo = []( Object&& o ) { o.doSomething(); };
condition? Object( p1 ) : Object( p1, p2, p3 );
    //doSomethingTo( condition? Object( p1 ) : Object( p1, p2, p3 ) );
}
