#include <iostream>
#include "Queue.h"
using namespace std;

int main()

{

 queue a;

 int data[5]={32,23,45,99,24};
 cout<<"Queue before adding Elements: ";
 a.display();
 cout<<endl<<endl;
 for(int iter = 0 ; iter < 5 ; iter++)
 {
   a.add(data[iter]);
   cout<<"Addition Number : "<<(iter+1)<<" : ";
   a.display();

   cout<<endl;

 }
 cout<<endl;
 cout<<"Queue after adding Elements: ";
 a.display();
 cout<<endl<<endl;
 
 for(iter=0 ; iter < 5 ; iter++)
 {
   a.del();
   cout<<"Deletion Number : "<<(iter+1)<<" : ";
   a.display();

   cout<<endl;
 }
 return 0;

}
