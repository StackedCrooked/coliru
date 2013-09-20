#include <stdio.h>
#include <time.h>

int main () {
    
  time_t rawtime;
  struct tm * timeinfo;
  char buffer [80];

  time (&rawtime);
  timeinfo = localtime (&rawtime);

  strftime (buffer, 80, "toupper(%b) %d %Y", timeinfo);  // SEP 15 2013
  puts (buffer);

  return 0;
}