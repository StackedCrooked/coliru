#include <iostream>

using namespace std;

int main()
{
    
   for (int i=1;i<=8;i++) 
   {
   for (int j=1;i>j;j++)
   cout<<" ";
   for (int j=8;i<=j;j--)
   cout<<"#";
   cout<<"\n";
   }
   return 0;
}