#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <stdlib.h>

using namespace std;

int StringToNumber(string s) {
    if (s == "A") { return 1; }
	else if (s == "B") { return 2; }
	else if (s == "C") { return 3; }
	else if (s == "D") { return 4; }
	else if (s == "E") { return 5; }
	else if (s == "F") { return 6; }
	else if (s == "G") { return 7; }
	else if (s == "H") { return 8; }
	else if (s == "I") { return 9; }
	else if (s == "J") { return 10; }
	
	return -1;
}

int main()
{
    while (true) {
        cout << "Input?\n";
        int x, y;
        while (true) {
        	cin.clear();
        	cin.ignore(numeric_limits<int>::max(), '\n');
        	string s;
        	cin >> s >> y;
        	x = StringToNumber(s);
        	if (x==-1 or y < 1 or y > 10) {
        		cout << "Wrong format. try again.\n";
        		continue;
        	}
        }
        cout << "input was " << x << ", " << y;
    }
}
