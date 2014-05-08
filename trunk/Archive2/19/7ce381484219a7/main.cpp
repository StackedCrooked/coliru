#include <iostream>
using namespace std;

int elapsedtime(int time1, int time2)
{
   return (time2-time1);
}

int main()
{
   int time1;
   int time2;
   cin >> time1 >> time2;
   cout << "Your elapsed time is " << elapsedtime <<endl;
}
