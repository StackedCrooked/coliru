#include <iostream>
#include <string>

using namespace std;


string input (void);
bool isValid (string);

string strFormel = "";
//string arrFormel[];


int main (int argc, char *argv[])
{
    cout << "Willkommen zum Kurvendiskussionsrechner!" << endl;
	strFormel = input ();

	// Teil eins: ID (Definitionsmenge)
	
	return 0;
}



string input ()
{
	string strInput = "";
	
	cout << "Bitte geben sie eine valide Gleichung ein:" << endl;
	cin >> strInput;
	cout << "Verarbeitung erfolgt..." << endl;
	
	if ( !isValid(strInput) )
	{
		cout << "Die Gleichung ist nicht valide. Versuchen Sie es erneut." << endl;
		strInput = input ();
	}
	else
	{
		cout << "Formel ist valide." << endl;
	}
	
	
	return strInput;
}



bool isValid (string valFormel)
{
	
	
	return true;
}