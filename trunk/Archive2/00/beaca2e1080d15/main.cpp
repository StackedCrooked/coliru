#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
   int i, n;
   double a, b, m;
   
   cout << "n = "; cin >> n;
   cout << endl;
   
   for(i=1; i <= n; i++)
   {
       cout << "Aluno: " << i << endl;
       cout << "a = "; cin >> a;
       cout << "b = "; cin >> b;
       m = (a + b)/2.0;
       cout << "Media = " << m << endl;
   }
   
   return 0;
}
