#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

char rot13(char c);
char rot13_lowercaseLetter(char c);
char rot13_uppercaseLetter(char c);
bool isLowercaseLetter(char c);
bool isUppercaseLetter(char c);
void empty(char *s, int length);


int main(int argc, char **argv)
{
    int phrase_length = 256;
    char phrase[phrase_length];
    char *input;
    int phrase_index = 0, i, j;
    for(i = 1; i < argc; i++) {
        input = argv[i];
        empty(phrase, phrase_length);
        for(j = 0; j < 256, input[j]; j++) {
            phrase[j] = rot13(input[j]);
        }
        cout << phrase << ' ';
    }
    cout << endl;
    return 0;
}   

// function rot13_lowercaseLetter: 
//   input: A single lower-case letter
//   output: the Rotate-13 transform of that letter
char rot13_lowercaseLetter(char c) {
    return char(((int(c) - int('a') + 13) % 26) + int('a'));
}

// function rot13_uppercaseLetter: 
//   input: A single upper-case letter
//   output: the Rotate-13 transform of that letter
char rot13_uppercaseLetter(char c) {
    return char(((int(c) - int('A') + 13) % 26) + int('A'));
}

// function isLowercaseLetter:
//   input: A single character
//   output: True if the input is a lowercase letter
//           False otherwise
bool isLowercaseLetter(char c) {
    if( c < 'a' )
        return false;
    
    if( c > 'z' )
        return false;
    
    return true;
}

// function isUppercaseLetter:
//   input: A single character
//   output: True if the input is an uppercase letter
//           False otherwise
bool isUppercaseLetter(char c) {
    if( c < 'A' )
        return false;
    
    if( c > 'Z' )
        return false;
    
    return true;
}

char rot13(char c) {
    if(isLowercaseLetter(c))
        return rot13_lowercaseLetter(c);
    
    if(isUppercaseLetter(c))
        return rot13_uppercaseLetter(c);
        
    return c;
}

void empty(char *s, int length) {
    for(int i = 0; i < length; i++)
        s[i] = 0;
}