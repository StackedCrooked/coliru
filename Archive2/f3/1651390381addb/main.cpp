#include <string>
#include <iostream>

time_t string_time(std::string date)
{
    struct tm tm;
    time_t val;
    //memset(&tm, 0, sizeof(struct tm));
    strptime(date.c_str(),"%FT%T%z",&tm);
    val = mktime(&tm);
    printf("%ld\n", (long)val);
    return val;
}
 
int main()
{
    time_t val = string_time("2010-11-04T23:23:01Z");
    time_t val2 = string_time("2010-11-05T01:23:01Z");
    
    double val3 = difftime(val2, val);
    printf("%d", (int)val3);
}   