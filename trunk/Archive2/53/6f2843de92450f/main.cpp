#include <iostream>
#include <iomanip>
#include <ctime>
 
int main()
{
    std::time_t t = std::time(NULL);
    std::tm tm = *std::localtime(&t);
    std::cout << "Today is           " << std::put_time(&tm, "%c %Z") <<'\n';
    tm.tm_mon -= 100;  // tm_mon is now outside its normal range
    std::mktime(&tm);
    std::cout << "100 months ago was " << std::put_time(&tm, "%c %Z") << '\n';
}