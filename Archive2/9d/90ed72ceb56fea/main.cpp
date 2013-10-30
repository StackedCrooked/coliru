#include <iostream>
#include <sstream>
using namespace std;

/**
    Makes the entire POSTNET "A" bar code for a ZIP code.

    @param zip the code to convert to a barcode.
    @return a bar code of the zip using "|" as the long
    bar and "," as the half bar.
*/
string buildBarcode(int zip);

/**
    Turns a single digit into a bar code.

    @param digit the single integer digit to encode.
    @return a bar code of the digit using "|" as the long
    bar and "," as the half bar.
*/
string buildDigit(string digit);


string buildBarcode(int zip) {
    stringstream ss;
	ss << zip;
	string sub = ss.str();
	string stuff = ""; //buildBarcode(zip);
	for (int i = 0; i < 4; i++) {
		stuff += buildDigit(sub.substr(i, i+1));
}
return stuff;
}

string buildDigit(int digit) {
	string theBar;
	if (digit == 0) {
		theBar = "||,,,";
	} else if (digit == 1) {
		theBar = ",,,||";
	} else if (digit == 2) {
		theBar = ",,|,|";
	} else if (digit == 3) {
		theBar = ",,||,";
	} else if (digit == 4) {
		theBar = ",|,,|";
	} else if (digit == 5) {
		theBar = ",|,|,";
	} else if (digit == 6) {
		theBar = ",||,,";
	} else if (digit == 7) {
		theBar = "|,,,|";
	} else if (digit == 8) {
		theBar = "|,,|,";
	} else if (digit == 9) {
		theBar = "|,|,,";
	} else { 
		theBar = "Please enter a number.";
	}
	return theBar;
}

int main() {
int barC = 1;
while (barC != 0) {
	cout << "Enter a zip code and I will generate a bar code." << endl;
	cin >> barC;
	string result = buildBarcode(barC);
	cout << result << endl;
	cout << barC << endl;
	
}
return 0;
}