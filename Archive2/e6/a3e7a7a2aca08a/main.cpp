#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;
// function expects the string in format dd/mm/yyyy:
bool extractDate(const std::string& s, int& d, int& m, int& y){
    std::istringstream is(s);
    char delimiter;
    if (is >> d >> delimiter >> m >> delimiter >> y) {
        struct tm t = {0};
        t.tm_mday = d;
        t.tm_mon = m - 1;
        t.tm_year = y - 1900;
        t.tm_isdst = -1;

        // normalize:
        time_t when = mktime(&t);

        time_t tNow;

      //   time(&tNow);

          const struct tm *norm = localtime(&when);

      const struct tm *now = localtime(&tNow);       /* when I uncomment this line the code                              
                                                        does not accept future date   */



      // validate (is the normalized date still the same?):   
        return (norm->tm_mday == d    &&
                norm->tm_mon  == m - 1 &&
                norm->tm_year == y - 1900);
    }
    return false;
}


int main() {

    std::string s("11/01/2015");
    int d,m,y;

    if (extractDate(s, d, m, y))
        std::cout << "date " 
                  << d << "/" << m << "/" << y
                  << " is valid" << std::endl;
    else
        std::cout << "date is invalid" << std::endl;
}