#include <iostream>
#include <string>
#include <vector>



int main()
{
    std::string przyszedl="przyszedł";
    std::string przeszedl="przeszedł";
    przyszedl=przeszedl;
    std::cout << (przyszedl == przeszedl? "ja" : "nie") << std::endl;
}
