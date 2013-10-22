#include <iostream>
#include <iomanip>
using namespace std;

int main ()
{
    char userName[50];
	char userResponse[100];

	cout << "Please enter your name: ";
	cin.getline(userName, 50);

	cout << left << endl << userName << " is a weirdo." << endl
			<< "MWAHAHAHAHAHALOLOLOLOLOL" << endl;

	cout << "Enter your response: ";
	cin.getline(userResponse, 100);

	cout << endl << "Whatever noob.";

	return 0;
}
