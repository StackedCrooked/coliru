#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    vector <string> c;
	string s;
	bool exit = false;
	while (getline(cin, s) && !exit) {
		if (s == "EXIT") {
			exit = true;
		}
		else {
			c.push_back(s);
			cout << s.size() << "\t" << s << "\n";
		}
	}

	int max = 0;
	for (int i = 1; i < c.size(); i++) {
		if (c[i].size() > c[max].size()) 
			max = i;		
	}
	while (cin>>s)
	cout << c[max].size() << "\t" << c[max] << "\n";
	return 0;