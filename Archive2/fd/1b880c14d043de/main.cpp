#include <iostream>
#include <boost/algorithm/string.hpp>
using namespace std;

int main() {
    string path = "C:\\path";
	boost::replace_all(path, "\\", "\\\\");
	cout << path << endl;
	return 0;
}