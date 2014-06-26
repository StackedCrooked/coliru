#include <stdio.h>

void stupidLegacyFunction(char *str) {
    puts(str);
}

//our code:
int main() {
    const char *str = "Hello, world!";
    
    //oh crap; we have to use the stupid function
    stupidLegacyFunction(const_cast<char *>(str));
}