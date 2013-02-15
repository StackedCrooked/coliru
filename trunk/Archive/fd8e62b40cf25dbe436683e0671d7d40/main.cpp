#include <iostream>
#include <string>
#include <algorithm> //requried for remove()
using namespace std;

//Checks to see if an inputed phrase is a palindrome regardless of letter case or punctuation

int main() {
    int len = 0;
    string input = "", cleanedString = "";
    char c = 'a';

	cout << "Enter a potential palindrome: ";
	getline(cin, input);

    //input = "racec ar!";
    input = "A man, a plan, a canal, panama!";
    //input = "Madam, I'm Adam";
    
	// Makes a copy of input to clean
    cleanedString = input;
    
    
    // Removes Spaces. .erase() takes (start location, # of characters to erase), remove() takes (start, end, character to search for)
    // [when remove() finds the character, it moves everything behind it forward one. Erase() trims off the end (that is now blank)]
    //cleanedString.erase(remove(cleanedString.begin(), cleanedString.end(), ' '), cleanedString.end());

    // Takes copied string, changes uppercase to lowercase & removes punctuation
	for (int i = 0; i < cleanedString.length(); i++) {
		c = cleanedString[i];
        
        cout << endl << c;

		if ((c >= 'A') && (c <= 'Z')) {
			c = c + 32;
			cleanedString[i] = c;
		} else if ((c >= 'a') && (c <= 'z')) {
			continue;
		} else {
    	    cleanedString.erase(i,1);
		}
        
        cout << " " << c;
	}
    
    
    // Palindrome Checker
    // Compares 1st value to last value, then moves both inward by 1.
	len = cleanedString.length() - 1;

    //cout << endl << len << endl;

	for(int i = 0; i < cleanedString.length(); i++) {
        
        //cout << cleanedString[i] << " " << cleanedString[len-i] << endl;
        
		if (cleanedString[i] == cleanedString[len-i]) {
			continue;
		} else {
			cout << endl << "\"" << input << "\"" << " is not a palindrome." << endl;
			return 0;
		}
	}

	cout << endl << "\"" << input << "\" is a palindrome!";

	return 0;
}