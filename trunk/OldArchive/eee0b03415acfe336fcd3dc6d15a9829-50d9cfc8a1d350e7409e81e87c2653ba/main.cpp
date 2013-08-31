#include<iostream>
#include<iomanip>
#include<fstream>
//#include<boost/regex.hpp>
//#include"ContactRec.h"
using namespace std;
//using namespace boost;
int GetOption();
int main(){GetOption();}
void GetContactInfo()
{
  /*  ContactRec id;
    ofstream myoutfile("directory.txt",ios::app); 
    regex reg_email("^\\w+([\\.-]?\\w+)*@\\w+([\\.-]?\\w+)*(\\.\\w{2,3})+$");
    regex reg_tel("^\\(?(\\d{3})\\)?-?(\\d{3})-(\\d{4})$"); 

        cout<<"enter your name."<<endl;
        cin.ignore(1024,'\n');
        getline(cin,id.Name);

        cout<<"enter your email."<<endl;
        cin>>id.Email;
        while (regex_match(id.Email,reg_email)==0)
        {
            cout<<"data wrong!!!!!!"<<endl;
            cin>>id.Email;
        }
        cout<<"enter your telephone numbers. EX:012-111-1111"<<endl;
        cin>>id.Phone;
        while(regex_match(id.Phone,reg_tel)==0)
        {
            cout<<"data wrong!"<<endl;
            cin>>id.Phone;
        }
        cout<<"Please enter the type(0)Family,(1)Friend,(2)Other"<<endl;
        int p;
        cin>>p;
        id.Type=(ContactType)p;
        myoutfile<<setiosflags(ios::left)<<setw(30)<<id.Name;
        myoutfile<<setiosflags(ios::left)<<setw(30)<<id.Email;
        myoutfile<<setiosflags(ios::left)<<setw(30)<<id.Phone;
        myoutfile<<setiosflags(ios::left)<<setw(30)<<id.Type<<endl;
        myoutfile.close();*/
    //return ;
}
void PrintContactInfo(int type)
{   /*
    ContactRec person;

        ifstream myinfile;
        myinfile.open("directory.txt",ios::in);
        cout<<setiosflags(ios::left)<<setw(30)<<"name";
        cout<<setiosflags(ios::left)<<setw(30)<<"email";
        cout<<setiosflags(ios::left)<<setw(30)<<"telephone";
        cout<<setiosflags(ios::left)<<setw(30)<<"type"<<endl;

    string temp;
    if (type==-1)
    {
        while (myinfile)
        {
            getline(myinfile,temp);
            cout<<temp<<endl;

        }
    }
    else if(type==0)
    {
        while (myinfile)
        {
            getline(myinfile,temp);
            if (temp[70]=='0')
                cout<<temp<<endl;

        }
    }
    else if(type==1)
    {
        while (myinfile)
        {
            getline(myinfile,temp);
            if (temp[70]=='1') 
                cout<<temp<<endl;

        }
    }   
    myinfile.close();*/
}
int GetOption()
{
    int number=0;
    while(number!=5)
    {
        cout<<"(1)Add a new record"<<endl;
        cout<<"(2)Display the all contacts."<<endl;
        cout<<"(3)Display the contacts of family. "<<endl;
        cout<<"(4)Display the contacts of friends."<<endl;
        cout<<"(5)Exit."<<endl;
        cin>>number;
        if (number==1)
        GetContactInfo();
        if (number==2)
        PrintContactInfo(-1);
        if (number==3)
        PrintContactInfo(0);
        if (number==4)
        PrintContactInfo(1);

    }
    return 1;
}