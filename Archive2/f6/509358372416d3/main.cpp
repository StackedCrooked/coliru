#include <iostream>
#include <fstream>
#include <stdint.h>
#include <errno.h>
#include <cstring>
#include <bitset>
#include <vector>

using namespace std;

vector<uint64_t> bytes;
vector<uint64_t>::iterator it;


int main()
{

    cout << "hi";

	char buffer[100];

	//string s = std::bitset< 64 >(12345).to_string(); // string conversion

	fstream myfile;
	myfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	myfile.open("C:\\Users\\Amaze SUCH WOW\\Desktop\\Recording_2014-12-24_20-47-31_0002.ts", ios::in | ios::out | ios::binary);
	myfile.read(buffer, 100);

	cout << " " << uint64_t(buffer[99]) << " ";

	it = bytes.begin();
	it = bytes.insert(it, buffer[99]);
	cout << bytes[0];

	cout << " " << uint64_t(buffer[54]) << " ";

	it = bytes.begin();
	it = bytes.insert(it, buffer[54]);
	cout << bytes[1];

	myfile.close();
	cin.get();
	return 0;
}