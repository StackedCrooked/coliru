#include <iostream>
#include <string>

int main()
{
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;

    const char * str = "2014-06-10 20:05:57";

    if (sscanf(str, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &min, &sec) == 6)
    {
        // sscanf returns the number of elements "parsed", so 6 means the string had all 6 elements.
        // Else it was probably malformed.
        
        std::cout << "day...: " << day   << std::endl;   
        std::cout << "month.: " << month << std::endl;
        std::cout << "year..: " << year  << std::endl;
        std::cout << "hour..: " << hour  << std::endl;
        std::cout << "min...: " << min   << std::endl;
        std::cout << "sec...: " << sec   << std::endl;
    }

    return 0;
}
