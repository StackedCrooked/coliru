#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<ofstream> v;
	v.emplace_back(std::string("file1.txt"));
	v.emplace_back(std::string("file2.txt"));
	for (int i = 0, ilen = v.size(); i < ilen; ++i)
		v[i] << "Test" << i << endl;
}
