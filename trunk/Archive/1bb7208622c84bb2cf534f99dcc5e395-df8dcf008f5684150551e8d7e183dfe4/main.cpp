#include <iostream>
#include <ctime>
#include <stdio.h>

#define LOGGING

#ifdef _WIN32
#    ifdef DLL_EXPORT
#        define LIBRARY_API __declspec(dllexport)
#    else
#        define LIBRARY_API __declspec(dllimport)
#    endif
#endif
#ifndef _WIN32
#    define LIBRARY_API
#endif

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

#define _INFO(format, args...)  \
	{ \
    time_t t = time(0);\
    struct tm * now = localtime( & t );\
    fprintf(stdout, "[INFO  %d-%d-%d %d:%d:%d]: ",now->tm_year + 1900,\
            now->tm_mon + 1, now->tm_mday,\
            now->tm_hour, now->tm_min, now->tm_sec); \
    fprintf(stdout, format , ## args);\
    printf("\n"); \
    fflush(stdout);\
	}

int main() {
    _ERROR("%d", 5);   
}