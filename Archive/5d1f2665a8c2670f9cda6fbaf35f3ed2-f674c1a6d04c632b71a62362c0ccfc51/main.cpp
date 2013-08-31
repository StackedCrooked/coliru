#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


using namespace std;

namespace
{
    struct digit
	{
		int arabic;
		char roman;
	};

	const digit digits[]{
		{1, 	'I'},
		{5,		'V'},
		{10,	'X'},
		{50,	'L'},
		{100,	'C'},
		{500,	'D'},
		{1000,	'M'}
	};

	const unsigned int nrOfDigits = (sizeof(digits) / sizeof(digit)) - 1;
}


string ArabicToRoman(int arabic)
{
	string roman = "";
	for(int digit = nrOfDigits; digit >= 0; digit--)
	{
		while(arabic >= digits[digit].arabic)
		{
			roman += digits[digit].roman;
			arabic -= digits[digit].arabic;
		}

		int smallerByIndex = ((digit + 1) % 2) + 1;
		if( digit > 0
			&& 	arabic - (arabic % (digits[digit].arabic - digits[digit-smallerByIndex].arabic))
				==
				digits[digit].arabic - digits[digit-smallerByIndex].arabic
			)
		{
			roman += digits[digit-smallerByIndex].roman;
			roman += digits[digit].roman;
			arabic -= (digits[digit].arabic - digits[digit-smallerByIndex].arabic);
			continue;
		}
	}
	return roman;
}


int RomanToArabic(const string& roman)
{
	int arabic = 0;
	unsigned int index = 0;

	for(int digit = nrOfDigits; digit >= 0; digit--)
	{
		if(	roman.size() > index
			&& roman[index] == digits[digit].roman
			)
		{
			if(digit < (int)nrOfDigits
				&& digits[digit + 1].roman == roman[index + 1]
				)
			{
				arabic += digits[digit + 1].arabic - digits[digit].arabic;
				index+=2;
				continue;
			}
			else if(digit + 1 < (int)nrOfDigits
					&&  digits[digit + 2].roman == roman[index + 1]
					 )
			{
				arabic += digits[digit + 2].arabic - digits[digit].arabic;
				index+=2;
				continue;
			}
		}

		while(roman[index] == digits[digit].roman)
		{
			arabic += digits[digit].arabic;
			index++;
		}
	}

	return arabic;
}


int main() {
	for(int i = 1; i<=3999; i++)
	{
		string roman = ArabicToRoman(i);
		int arabic = RomanToArabic(roman);
		cout << i << " == " << roman << " == " << arabic << endl;
		assert(i == arabic);
	}
	return 0;
}
