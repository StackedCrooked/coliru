#include <iostream>
using namespace std;

double* maximum(double* a, int size)
{
   if (size == 0)
   {
      return NULL;
   }
   double* m = a;
   double* p = a;
   for (int i = 0; i < size; i++)
   {
      if (*p > *m)
      {
         m = p;
      }
      p++;
   }
   return m;
}

int main()
{
   double data[] = {};
 double* max = maximum(data, 0);
   cout << *max << endl;
   return 0;
}