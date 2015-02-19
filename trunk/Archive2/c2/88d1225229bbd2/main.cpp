#include <iostream>
int main()
{
using namespace std;
int mat[5][5];
    for(int j=0;j<5;j++)
       {
           for(int i=0;i<5;i++)
              {
                   cout<<"Digite um elemento:";
                   cin>>mat[i][j];
              }
       }
return 0;
}