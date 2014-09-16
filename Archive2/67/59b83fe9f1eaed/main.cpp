#include <iostream>
#include <string>
#include <cctype>
#include <cstring>

void wordWrapPrinting(const char* s, int len=-1);

int main()
{
     std::cout << "Hello, my name is ________. This is a test of my word wrap program. If it works as      intended, it will correctly fix strings such as this one and make sure that none of the words are cut off and carried over to another line. This will make writing stories for games much easiser for both myself and Kevin, and maybe even the whole class. This was a request from _____ (sort of, he was complaining about it and I said I could probably make one). Hopefully this works...  AndTheReallyHardPartIsWhatIfWe'reGivenVeryLongWordsThenWhenDoWeLinebreaIMeanReally,It'sQuiteThePredicament!?";
     std::cout << "\n\n\n\n\n";
     wordWrapPrinting("Hello, my name is ________. This is a test of my word wrap program. If it works as intended, it will correctly fix strings such as this one and make sure that none of the words are cut off and carried over to another line. This will make writing stories for games much easiser for both myself and Kevin, and maybe even the whole class. This was a request from _____ (sort of, he was complaining about it and I said I could probably make one). Hopefully this works...  AndTheReallyHardPartIsWhatIfWe'reGivenVeryLongWordsThenWhenDoWeLinebreakIMeanReally,It'sQuiteThePredicament!?");
}

void wordWrapPrinting(const char* s, int len)
{
    if (len < 0)
        len = std::strlen(s);
    while(len > 79) {
        int i=79;
        while(i>0 && isspace(s[i])==false) 
            --i;
        if (i==0)
            i=79;
        std::cout.write(s, i+1);
        std::cout << '\n';
        s += i+1;
        len -= i+1;
    }
    std::cout.write(s, len);
}