#include <cstdio>

using namespace std;

int main()
{
   int i, *p;
   for (i=0; i<5; i++)
   {
       scanf("%d", (p+i));
       printf("%d", *(p+i));
   }
   return 0;
} 
