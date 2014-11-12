#include <iostream>
#include <functional>

using namespace std;

/////////////////////////// My library
// functor
    struct FuncWrapper
	{
		bool UseUserFunction; // just a flag;

		std::function<float(float)> foo; // the function used

		float def( float v ) // the default behaviour member function definition
		{
			return v*3;
		}

		float operator()( float v ) // call of function
		{
			return foo(v);
		}

		void AssignFunction( float (*uf)(float) ) { foo = uf; }

	// constructor: initialises to default function
		FuncWrapper() : UseUserFunction(false), foo(&FuncWrapper::def) {}
	};
///////////////////////////   /My library

// the function the user needs
float MyFunction( float v )
{
	return v*2;
}

int main()
{
    cout << "start\n";
	FuncWrapper f;
	cout << "default " << f(2) << endl; // should print "6"

	f.UseUserFunction = true;
	f.AssignFunction( myFunction );
	cout << "now is: " << f(2) << endl; // should print "4"
}

