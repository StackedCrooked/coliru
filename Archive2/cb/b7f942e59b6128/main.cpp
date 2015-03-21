#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

template <typename... Rest>
void callPrintf(const char* const format, Rest...) __attribute__((format(printf, 1, 2)));                                                                                                               
                                                                                                                                                                                                    
template <typename... Rest>                                                                                                                                                                         
void callPrintf(const char* const format, Rest... rest)                                                                                                                                             
{                                                                                                                                                                                                   
  printf(format, rest...);                                                                                                                                                                          
}

int main()                                                                                                                                                                                          
{                                                                                                                                                                                                   
  callPrintf("%d %lf\n", 1, 2.0);                                                                                                                                                                   
  return 0;                                                                                                                                                                                         
}