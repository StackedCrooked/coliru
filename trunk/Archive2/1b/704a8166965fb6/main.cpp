#include <iostream>
#include <fstream>
#include <stdint.h>
#include <errno.h>

using namespace std;


int main()
{

    cout << "hi";

	char buffer[100];

	fstream myfile;

	myfile.open("C:\\Users\\Amaze SUCH WOW\\Desktop\\Recording_2014-12-24_20-44-34_0002.ts", ios::in | ios::out | ios::binary);
	if (!myfile) {
		cout << "shit: " << strerror(errno);
	}
	myfile.read(buffer, 100);
	if (!myfile.read(buffer, 100))
	{
		cout << "Error2";
	}

	cout << " " << int64_t(buffer[44]);
	myfile.close();

	cin.get();
	return 0;
}