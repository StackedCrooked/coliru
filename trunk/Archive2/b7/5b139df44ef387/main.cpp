#include <functional>
#include <iostream>

using namespace std;

struct Aap
{
    void meh( string str ){ cerr << str << "   = " << this << endl; }
};

int main()
{    
    Aap aap;
    
    cerr << "aap = " << &aap << endl;
    
    auto a = bind( &Aap::meh, &aap, "a" );
    a();
    
    auto b = bind( &Aap::meh, aap, "b" );
    b();
    
    return 0;
}