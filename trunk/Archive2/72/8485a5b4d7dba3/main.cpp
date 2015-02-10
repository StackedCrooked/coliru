#include<iostream>
#include<cctype>
#include<ctime>
#include <time.h>
#include <sys/time.h>
using namespace std;
static inline bool is_digit(char c)
{
    return c>='0'&&c<='9';
}
int main()
{
    char c='8';
    struct timeval tvSt, tvEn;
    //time_t t1=clock(),t2,t3;
    gettimeofday(&tvSt, 0);
    for(int i=0;i<1e9;i++)
        is_digit(c);
    gettimeofday(&tvEn, 0);
    cout << "is_digit:" << (tvEn.tv_sec - tvSt.tv_sec)*1000000 + (tvEn.tv_usec - tvSt.tv_usec) << " us"<< endl;
    gettimeofday(&tvSt, 0);
    for(int i=0;i<1e9;i++)
        isdigit(c);
    gettimeofday(&tvEn, 0);
    cout << "isdigit:" << (tvEn.tv_sec - tvSt.tv_sec)*1000000 + (tvEn.tv_usec - tvSt.tv_usec) << " us"<< endl;

    return 0;
}