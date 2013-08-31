#include <iostream>     // std::ostream, std::cout, std::cin
#include <fstream>      // std::ofstream
#include <string>
#include <algorithm>

std::string line ( std::string str ) {
    std::string::iterator it1 = str.begin()+7;
    for ( ;it1 != str.end(); it1++ ) {
        if (!isspace(*it1)) { it1++; break; };
    }
    std::string::iterator it2 = str.end();
    for (int i = str.size();it2 != it1; --it2, --i) {
        if ( (i < 72) && (!isspace(*it2)) ) { it2++; break; }
    }    
    std::string ia (it1, it2);
    return ia;
}

/*
std::string eol ( std::string str ) {
    std::string::iterator it = str.end();
    for (int i = str.size();it != bol(str); --it, --i) {
        if ( (i < 72) && (!isspace(*it)) ) { it++; break; }
    }
    std::string ia (str.begin(), it);
    return ia;
}
*/
/*
std::string line ( std::string str ) {
    std::string s (bol(str), eol(str));
    return s;
}
*/

int main () {
  std::string str("      *   #DESCRIPTION                                                  123");
  std::string str2 = line(str);
  std::cout << str2 << std::endl;
  std::cout << str2.size() << std::endl;

  return 0;
}