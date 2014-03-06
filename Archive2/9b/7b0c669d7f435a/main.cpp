// Strings, Chars, and Regex.
// Author: LLD!5DeRpYLOvE

#include <string>
#include <iostream>
#include <cctype>
#include <vector>
//#include <iterator>

//#include <regex>

using std::string;
using std::cout;
using std::endl;
using std::toupper;
using std::vector;
//using std::begin;
//using std::end;

int main()
{
    // Some source strings and stuff
    string conscious{ "To be conscious that you are ignorant is a great step to knowledge." };
    string autocorrect{ "I think YOU had one of those autocorrect problems sir." };
    string leapstep{ "That's one small step for man, one giant leap for Mankind." };
    string ourselves{ "It is not in the stars to hold our destiny but in ourselves." };
    string onelife{ "One life, you're Thomas A. Anderson, program writer for a respectable software company." };
    string hellothere{ "Hello from planet Earth." };
    string makesure{ "Before you say you can't, make sure you've tried." };
    
    string maryaddr{ "Mary Lamb\n1192 Woolen Way\nLambsville, MD 13956" };
    
    // STRINGS
    //================
    
    // String concatenation is likely the simplest string modification to use.
    cout << makesure << endl;
    string isnotry{ "\n\"There is no try.\" -Yoda" };
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
    a[12] = '?';
    cout << a << " Why hello there." << endl << endl;
    
    // You can replace portions of a string with other text. Just indicate where to start, how many
    //  chars to replace starting from there, and the text you want to use instead.
    cout << "before: " << autocorrect << endl;
    autocorrect.replace(8, 3, "you");
    cout << "after:  " << autocorrect << endl << endl;
    
    // With replace(), it's unnecessary that the replacement text be the same number of chars as the section being replaced.
    cout << onelife << endl;
    string otherlife{ "The other life is lived in computers, where you go by the hacker alias 'Neo' and are guilty of virtually every computer crime we have a law for." };
    onelife.replace(onelife.begin(), onelife.end(), otherlife);
    cout << onelife << endl;
    //
    // And of course any existing strings can simply be reassigned to, just like other types can be.
    onelife = "You're going to help us Mr. Anderson, whether you want to--or not.";
    cout << onelife << endl << endl;
    
    // REGEX
    //================

    // Parsing individual words/counts
    vector<string> my_strings{ conscious, autocorrect, leapstep, ourselves, onelife, hellothere, makesure };
    for(auto elem : my_strings)
        cout << elem << endl;
    //
            
    
//    // Finding address info
//    struct myaddr {
//        string name{""};
//        string street{""};
//        string city{""};
//        string state{""};
//        string zip{""};        
//    };
//    cout << maryaddr << endl;

}