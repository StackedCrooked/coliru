#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

bool isVowel (char ch)
{
    ch = toupper(ch);
	return ch =='A'|| ch=='E' || ch=='I' || ch=='O' || ch=='U';
}

void counter(std::istream &iss) {
	int v(0), c(0), d(0), l(0), r(0), 
	sq(0), dq(0), other(0), ch;
	
	while (iss) {
		switch(ch = iss.get()) {
			case '(':
				l++;
				break;
			case ')':
				r++;
				break;
			case '\'':
				sq++;
				break;
			case '\"':
				dq++;
				break;
		}
		
		if (isalnum(ch)) {
			isdigit(ch) ? d++ : isVowel(static_cast<char>(ch)) ? v++ : c++;
		}
		else other++;
	}
	
	std::cout << "\tSummary:\n"
	<< "Total characters: " << v + c + d + l + r + sq + dq + other << '\n'
	<< "Vowels: " << v << '\n'
	<< "Consonants: " << c << '\n'
	<< "Letters: " << v + c << '\n'
	<< "Digits: " << d << '\n'
	<< "Left parentheses: " << l << '\n'
	<< "Right parentheses: " << r << '\n'
	<< "Single quotes: " << sq << '\n'
	<< "Double quotes: " << dq << '\n'
	<< "Other: " << other << endl << endl;
}

int main ()
{
	ifstream inFile(__FILE__);

	if ( inFile.fail() )
	{
		cout << "The file " << __FILE__ << " failed to open.";
		return 1;
	}
	
	counter(inFile);
	return 0;
}