#include <iostream>
#include <stdio.h>

using namespace std;

struct StudentRecord
{
       string name;
       string age; 
       string address;
       string email;
       string gender;
} 

StudentR[4]; 

int main()
{
    int i;
    
    for (i=0;i<4;i++)
    {
        cout << "Student_Name: ";
        getline(cin,StudentR[i].name);
        cout<<"Student_Age: ";
        getline(cin,StudentR[i].age);
        cout<<"Student_Address: ";
        getline(cin,StudentR[i].address);
        cout<<"Student_Email: ";
        getline(cin,StudentR[i].email);
        cout<<"Student_Gender: ";
        getline(cin,StudentR[i].gender);
        cout<<endl;
    }
    
       for (i=0;i<4;i++)
   {
         cout<<""<<endl;
         cout<<""<<endl;
         cout<<"Student_Name :Abu "<<StudentR[i].name<<endl;
         cout<<"Student_Age:126 "<<StudentR[i].age<<endl;
         cout<<"Student_Address:1984 "<<StudentR[i].address<<endl;
         cout<<"Student_Email:28 "<<StudentR[i].email<<endl;
         cout<<"Student_Gender:28 "<<StudentR[i].gender<<endl;
   }     

system("Pause");
return 0;
}
