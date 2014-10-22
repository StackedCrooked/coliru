#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;


string findItem(string *array, int size, string target)
{
    int index = 0;
	bool found = false ;

	while (!found && (index < size))
	{
		if (target == array[index])
			found = true ;

		else
			index++;
	}


	if (!found)
		throw runtime_error("Target not found in a array!");

	return array[index];
}


int main(){

	string stuff[5] = {"Keys", "Food", "Glasses", "Cheese", "Skeleton"};

	string a_thing;

	try
	{
		a_thing = findItem(stuff, 5, "Pants");

	}

	catch(runtime_error& runErr)
	{
                //runErr.what() still prints nothing.
		cout << runErr.what() << endl;
		cout << "runtime_error" << endl;

		a_thing = "Nothing";


	}

	cout << a_thing << endl;

	return 0;

}
