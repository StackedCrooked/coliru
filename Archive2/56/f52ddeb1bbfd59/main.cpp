#include <iostream>
#include <string>

int main()
{
    std::string s = "25\u00B2"; // works in a string
    char x = '\u00B2';
    s.append(1, x);
    
    std::cout<<s<<"\n\n";
    for(unsigned char c : s) {
        std::cout<<std::hex<<static_cast<unsigned int>(c)<<"\n";
    }
    return 0;
}
