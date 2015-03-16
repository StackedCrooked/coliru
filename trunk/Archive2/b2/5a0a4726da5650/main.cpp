#include <iostream>
#include <string>
#include <vector>


enum Roman {
    I = 1,
	II,
	III,
	IV,
	V,
	VI,
	VII,
	VIII,
	IX,
	X,
	XX = 20,
	XXX = 30,
	XL = 40,
	L = 50,
	LX = 60,
	LXX = 70,
	LXXX = 80,
	XC = 90,
	C = 100,
	CC = 200,
	CCC = 300,
	CD = 400,
	D = 500,
	DC = 600,
	DCC = 700,
	DCCC = 800,
	CM = 900,
	M = 1000,
	MM = 2000,
	MMM = 3000
};

std::string RomanToStr(int r)
{
    switch (r)
	{
	case I:
		return "I";
	case II:
		return "II";
	case III:
		return "III";
	case IV:
		return "IV";
	case V:
		return "V";
	case VI:
		return "VI";
	case VII:
		return "VII";
	case VIII:
		return "VIII";
	case IX:
		return "IX";
	case X:
		return "X";
	case XX:
		return "XX";
	case XXX:
		return "XXX";
	case XL:
		return "XL";
	case L:
		return "L";
	case LX:
		return "LX";
	case LXX:
		return "LXX";
	case LXXX:
		return "LXXX";
	case XC:
		return "XC";
	case C:
		return "C";
	case CC:
		return "CC";
	case CCC:
		return "CCC";
	case CD:
		return "CD";
	case D:
		return "D";
	case DC:
		return "DC";
	case DCC:
		return "DCC";
	case DCCC:
		return "DCCC";
	case CM:
		return "CM";
	case M:
		return "M";
	case MM:
		return "MM";
	case MMM:
		return "MMM";
	default:
		std::cout << r << " - Unknown numeral\n";	
		return "";
	}
}

std::string decimalToRoman(int num)
{
	//std::cout << num << std::endl;
	if (num > 3999) return "The number is too big\n";

	std::string retVal;

	int curr(num);

	int div(10000);

	while (div > 1)
	{
		if (curr >= div) {
			int tmp = curr / div;
			retVal += RomanToStr(tmp * div);
		}
		curr %= div;
		div /= 10;
	}
	if (curr > 0) {
		retVal += RomanToStr(curr);
	}

	return retVal;
}

int main() {
    for (auto i(1); i <= 3000; ++i)
        std::cout << "--- roman("  << i << "): " << decimalToRoman(i) << std::endl; 
    return 0;
}
