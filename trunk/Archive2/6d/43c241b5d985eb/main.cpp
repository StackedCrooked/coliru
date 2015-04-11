#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
 
using namespace std;
 
int main() {
    // your code goes here
	struct tm now = { 0 };
	cout << "Please enter the 8-digit date (YYYYMMDD): " << endl;
	cin >> std::get_time(&now, "%Y%m%d");
    
    cout << "You entered " << put_time(&now, "%d.%m.%Y") << '\n';
}