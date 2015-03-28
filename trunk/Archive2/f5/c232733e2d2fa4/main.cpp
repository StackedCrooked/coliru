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
    string conscious{"To be conscious that you are ignorant is a great step to knowledge."};
    string autocorrect{"I think YOU had one of those autocorrect problems sir."};
    string leapstep{"That's one small step for man, one giant leap for Mankind."};
    string ourselves{"It is not in the stars to hold our destiny but in ourselves."};
    string onelife{"One life, you're Thomas A. Anderson, program writer for a respectable software company."};
    string hellothere{"Hello from planet Earth."};
    string makesure{"Before you say you can't, make sure you've tried."};
    
    // String concatenation is likely the simplest string operation to use.
    cout << makesure << endl;
    string isnotry{"\n\"There is no try.\" -Yoda"};
    makesure += isnotry;
    cout << makesure << endl << endl;
    
    // You can extract out substrings from other strings using substr().
    //  Start and end indexes indicate what range to extract out.
    cout << hellothere << endl;
    string a{hellothere.substr(11, hellothere.size() - 1)};
    cout << a << endl;
    //
    // You can inplace-modify chars within strings.
    a[0] = toupper(a[0]);
    a[12] = ',';
    cout << a << " hello." << endl << endl;
    
    // You can replace portions of a string with other text. Just indicate where to start, 
    //  how many chars to replace starting from there, and the text you want to use instead.
    cout << "before: " << autocorrect << endl;
    autocorrect.replace(8, 3, "you");
    cout << "after:  " << autocorrect << endl << endl;
    
    // With replace(), it's unnecessary that the replacement text be the same number of chars as that being replaced.
    cout << onelife << endl;
    string otherlife{"The other life is lived in computers, where you go by the hacker alias 'Neo' and are guilty of virtually every computer crime we have a law for."};
    //
    // Using iterators is a powerful and elegant way to work with elements of any data container--including the string class.
    //onelife.replace(0, onelife.size() - 1, otherlife);          // Instead of needing to use this form only,
    onelife.replace(onelife.begin(), onelife.end(), otherlife);   // you can use this clearer form instead.
    cout << onelife << endl << endl;
        
}