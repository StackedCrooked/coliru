#include <iostream>
#include <string>
#include <utility>
using namespace std;

class Base{
public:
    Base(const string& str):m_Str(str)
		{cout << m_Str << ": Use COPY constructor \n";};
	Base(string&& str):m_Str(move(str))
		{cout << m_Str <<": Use MOVE constructor \n";};
private:
	string m_Str;
};

int main()
{
	Base b("example"); // direct initialization: Use MOVE constructor

    // http://en.cppreference.com/w/cpp/language/copy_initialization
	Base b2 = string("second example") ; // copy initialization: Use MOVE constructor

    // copy initialization is less permissive than direct initialization
	// Base b3 = "third example" ; // *** error
}
