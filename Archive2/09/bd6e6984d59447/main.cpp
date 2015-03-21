#include <iostream>
#include <cstdio>
#include <string>
#include <cstdarg>
using namespace std;

template <char const* format, class... Rest>
int callPrintfLike(Rest&&... rest)                                                                                                                                                                  
{                                                                                                                                                                                                   
  return printf(format, std::forward<Rest>(rest)...);                                                                                                                                               
}

int main()                                                                                                                                                                                          
{                                                                                                                                                                                                   
  callPrintfLike<"%d %lf\n">(1, 2.0);                                                                                                                                                               
  return 0;                                                                                                                                                                                         
}
