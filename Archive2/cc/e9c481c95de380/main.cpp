#include <map>
#include <iostream>
using namespace std;

void testFunc() { cout<<"It works!\n"; }
void testFunc2() { cout<<"It too works!\n"; }

int main()
{
    map< int, void (*)() > mymap;//Why are 2 *'s required?
	// two *'s are not required if the mapped_type is just 'pointer to void()'

	void (*tt)() = &testFunc;
	mymap[1] = tt ;

	void (*final)();

	final = mymap.find(1)->second;

    final();

    {
        using function_type = void() ; // or: typedef void function_type() ;
        map< int, function_type* > mymap;

        mymap[1] = &testFunc ;
        mymap[9] = testFunc2 ; // equivalent to: &testFunc2

        mymap[1]() ;
        mymap[9]() ;
    }
}
