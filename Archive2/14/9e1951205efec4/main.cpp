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
    
system("Pause");
return 0;
}
