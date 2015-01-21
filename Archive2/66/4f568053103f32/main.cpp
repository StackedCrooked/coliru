#include <errno.h>
#include <string.h>

#include <stdarg.h>

#include <time.h>

int main()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
}