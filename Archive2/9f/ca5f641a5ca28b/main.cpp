// Strings, Chars, and Regex.
// Author: LLD!5DeRpYLOvE

#include <string>
#include <iostream>
#include <cctype>
//#include <iterator>
//#include <vector>
//#include <regex>

using std::string;
using std::cout;
using std::endl;
using std::toupper;
//using std::begin;
//using std::end;

int main()
{
    // Some source strings and stuff
    string hellothere{"Hello from planet Earth."};
    string conscious{"To be conscious that you are ignorant is a great step to knowledge."};
    string autocorrect{"I think YOU had one of those autocorrect problems sir."};
    string leapstep{"That's one small step for man, one giant leap for Mankind."};
    string ourselves{"It is not in the stars to hold our destiny but in ourselves."};
    string onelife{"One life, you're Thomas A. Anderson, program writer for a respectable software company."};
    string makesure{"Before you say you can't, make sure you've tried."};
    
    // You can extract out substrings from other strings.
    cout << hellothere << endl;
    string a{hellothere.substr(11, hellothere.size())};
    cout << a << endl;
    // You can transform individual chars inside strings.
    a[0] = toupper(a[0]);
    cout << a << " Hello." << endl << endl;
    
    // You can replace portions of a string with other text. Just indicate where to start, 
    //  how many chars to replace starting there, and the text you want to use insted.
    cout << "before: " << autocorrect << endl;
    autocorrect.replace(8, 3, "you");
    cout << "after:  " << autocorrect << endl << endl;
    
    // With replace(), it's unnecessary that the replacement text be the same number of chars as that being replaced.
    cout << onelife << endl;
    string otherlife{"The other life is lived in computers, where you go by the hacker alias 'Neo' and are guilty of virtually every computer crime we have a law for."};
    //onelife.replace(0, onelife.size(), otherlife);
    // Using iterators is a powerful and elegant way to work with elements from any data container--including the string class.
    onelife.replace(onelife.begin(), onelife.end(), otherlife);
    cout << onelife << endl << endl;
        
}