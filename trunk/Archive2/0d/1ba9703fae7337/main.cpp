#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

int main() {
        std::stringstream s;
    	s.str("");
    	if (s.fail())
    		cout << "bad"; // not printed
    	s.seekp(0);
    	// s.rdbuf()->pubseekpos(0, ios_base::out); // Equivalent as per 27.7.3.5/3
    	if (s.fail())
    		cout << "bad"; // printed
    }