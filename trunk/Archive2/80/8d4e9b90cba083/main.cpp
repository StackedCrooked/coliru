#include <iostream>

int main()
{
    unsigned char al = 53;
    unsigned char dl = 9;
    
    al = ~al; // not al
    ++al;     // inc al
    dl += al; // add dl, al
    
    std::cout << "al : " << int(al) << '\n'
              << "dl : " << int(dl) << std::endl;
}