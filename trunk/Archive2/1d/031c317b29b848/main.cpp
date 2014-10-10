#include <iostream>
#include <string>

using namespace std;

int main() {
    int count;
	string s;
	count = 0;
	while (getline(cin, s))
		count++;
	cout << count << '\n';
	return 0;
}