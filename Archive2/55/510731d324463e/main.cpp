#include <iostream>
#include<windows.h>
#include <cstdlib>
#include<conio.h>
using namespace std;
void std1()
{
     cout<<"your system is shutdown\n"<<endl;
	 cout<<"\nGOOD BYE!!!"<<endl;
   //system("shutdown -s -t 1");
}
void sleep(int &m,int &y,int &x)
{
	Sleep(1000*60*y*m);
	Sleep(1000*60*y);
   Sleep(1000*x);
   std1();
}
void cni()
{int y,x,m;
cout<<"ENTER HOURS"<<endl;
cin>>m;
cout<<"ENTER MINTUS "<<endl;
	cin>>y;
	cout<<"ENTER SEC"<<endl;
	cin>>x;
	sleep(m,y,x);
}
int cho()
{
	char t;
	cout<<"you want to shutdown press y or n for not"<<endl;
	cin>>t;
	if (t=='y'||t=='Y')
	{
		cni();
	}
	else if(t=='n'||t=='N')
		{
			cout<<"GOOD BYE!!!"<<endl;
			return 0;
			}
}
int main ()
{
	cho();
	system("pause");
}




