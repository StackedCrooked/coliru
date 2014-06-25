#include <stdio.h>

void stupidLegacyFunction(char *str) {
    puts(str);
}

//our code:
#include <string>

int main() {
    std::string str = "Hello, world!";
    
    //oh crap; we have to use the stupid function
    stupidLegacyFunction(const_cast<char *>(str.c_str()));
}