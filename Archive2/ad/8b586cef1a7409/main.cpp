#include <iostream>
#include<string>
using namespace std;
class student
{
    string name;
    double gpa;
    int course;
    public:
    void set(string,int,double);
    void print()
    {
        cout<<"name"<<name<<"\n"<<"course"<<course<<"\n"<<"gpa"<<endl;
    }
};
void student ::set(string a,int b,double c)
{
    name=a;
    course=b;
    gpa=c;
    
}
int main()
{
    student s1;
    string n;
    int a;
    double d;
    cin>>n>>a>>d;
    s1.set(n,a,d);
    s1.print();
   return 0;
}