#include <iostream>
#include <string>
#include <vector>

#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/algorithm/string/trim.hpp>

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int
main(void)
{
   struct tm tm;
   char buf[255];

   memset(&tm, 0, sizeof(struct tm));
   strptime("2001-11-12 18:31:01", "%Y-%m-%d %H:%M:%S", &tm);
   strftime(buf, sizeof(buf), "%d %b %Y %H:%M", &tm);
   puts(buf);
   exit(EXIT_SUCCESS);
}

