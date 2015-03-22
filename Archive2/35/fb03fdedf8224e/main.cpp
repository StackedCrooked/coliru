#include <string>
#include <iostream>

time_t string_time(std::string date)
{
    struct tm tm;
    time_t val;
    //memset(&tm, 0, sizeof(struct tm));
    //strptime(date.c_str(),"%FT%T%z",&tm);
    if (strptime(date.c_str(),"%FT%T%z",&tm)) {
        int d = tm.tm_mday,
        m = tm.tm_mon + 1,
        y = tm.tm_year + 1900;
        std::cout << y << "-" << m << "-" << d << " "
              << tm.tm_hour << ":" << tm.tm_min;
    }
    val = mktime(&tm);
    printf("%ld\n", (long)val);
    
    return val;
    
}
 
int main()
{
    time_t val = string_time("2015-03-22T02:16:17.000Z");
    time_t val2 = string_time("2015-03-22T02:17:47.000Z");
    
    double val3 = difftime(val2, val);
    printf("%d\n", (int)val3);
    
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    
    strftime (buffer,80,"Now it's %I:%M%p.",timeinfo);
    puts (buffer);
    
}   