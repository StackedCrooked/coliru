#include <iostream>
#include <string>
#include <algorithm>


int main()
{
    std::string str = "maria hernandez 1000 h3777 +1000 19:15:19\nrachel dominguez 100000 X8793 +100000 19:15:20\ncarlos yatch 20 g6386 +20 19:15:20\n\n\n\ncarlos Domingues 20 g3336 +20 19:15:20"; 
    std::cout << "Before:\n\n" << str << std::endl;
    
    str.erase(std::unique(str.begin(), str.end(),
                          [] (char a, char b) { return a == '\n' && b == '\n'; }),
              str.end());
          
    std::cout << "\nAfter:\n\n" << str <<std::endl;
    
    return 0;
}
