#include <string>
#include <iostream>
 
int main()
{
    const char * dateInput = "2010-11-04T23:23:01Z";
    // ....
    struct tm tm;
    time_t val;
    strptime(dateInput,"%y/%m/%d %H:%M:%S",&tm);
    val = mktime(&tm);
}