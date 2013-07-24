#include <cstdio> 
#include <ctime>

#define _ERROR(format, args...)  \
    { \
    time_t t = time(0);\
    struct tm * now = localtime( & t );\
    fprintf(stderr, "[ERROR %d-%d-%d %d:%d:%d]: ",now->tm_year + 1900,\
            now->tm_mon + 1, now->tm_mday,\
            now->tm_hour, now->tm_min, now->tm_sec); \
    fprintf(stderr, format , ## args);\
    printf("\n");\
    fflush(stderr);\
    }
    
int main() {
    _ERROR("%d", 5);   
}