#include <iostream>
#include <stdio.h>

using namespace std;
struct StudentRecord{
       string name;
       string age; 
       string address;
       string email;
       string gender;} 
       StudentR[4];       
int main()
{
    int i;
    for (i=0;i<4;i++)
    {
        cout<<"Name: ";
        getline(cin,StudentR[i].name);
        cout<<"Age: ";
        getline(cin,StudentR[i].age);
        cout<<"Address: ";
        getline(cin,StudentR[i].address);
        cout<<"Email: ";
        getline(cin,StudentR[i].email);
        cout<<"Gender: ";
        getline(cin,StudentR[i].gender);
        cout<<endl;
    }
  
     cout<<"StudentR[3].name: "<<StudentR[3].name<<endl;
     cout<<"StudentR[1].age: "<<StudentR[1].age<<endl;
     cout<<"StudentR[3].gender: "<<StudentR[3].gender<<endl;
     cout<<"StudentR[2].address: "<<StudentR[2].address<<endl;
system("PAUSE");
return 0;
}
