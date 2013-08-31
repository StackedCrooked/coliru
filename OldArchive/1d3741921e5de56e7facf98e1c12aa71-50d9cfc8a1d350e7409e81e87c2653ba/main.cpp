#include <iostream>
using namespace std;

int n, num, i, j=0;

int main()
{
  
  for (n=1 ; n<1000 ; n++)
  {
    num=(n*6)-1;
  
    for (i=2; i<num ; i++) {
        if (num%i==0) {
          j++;
          cout << num << ",divisible al menos por " << i << " nde gay" << endl;
        }
    }

    
  }
  
  if (j==0) cout << "Se cumple";
  else cout << "No se cumple";
    
   return 0;
}
   