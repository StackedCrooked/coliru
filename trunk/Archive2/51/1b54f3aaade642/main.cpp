#include <iostream>
#include <string>
#include <cstring>
using namespace std;





std::string ToString()
{
   std::string ret( 6, 'a');
   char* str = new char[6]();
   strcpy(str, "Jagan");
   std::swap( ret[0], *str);

    return ret;
}

int main (){
    std::string s = ToString();
    std::cout << s;
}