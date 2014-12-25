#include <iostream>
#include <fstream>
#include <stdint.h>
#include <errno.h>
#include <cstring>

using namespace std;


int main()
{

    cout << "hi";

	char buffer[100];

	fstream myfile;
	myfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	myfile.open("C:\\Users\\Amaze SUCH WOW\\Desktop\\Recording_2014-12-24_20-44-34_0002.ts", ios::in | ios::out | ios::binary);
	if (!myfile) {
		cout << "shit: " << strerror(errno);
	}
	myfile.read(buffer, 100);
	if (!myfile.read(buffer, 100))
	{
		cout << "shit: " << strerror(errno);
	}

	cout << " " << uint64_t(buffer[23]);
	myfile.close();

	cin.get();
	return 0;
}