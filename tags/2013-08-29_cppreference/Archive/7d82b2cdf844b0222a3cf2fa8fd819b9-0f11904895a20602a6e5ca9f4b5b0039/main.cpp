#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

int main() {
    std::string txt ("");

    printf("Enter string:\n");
    std::getline(std::cin, txt);

    printf("\n\"%s\" has %i characters.", txt, txt.length());

    return 0;
}
