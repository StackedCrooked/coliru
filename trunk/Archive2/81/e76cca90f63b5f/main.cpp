#include <iostream>
#include <string>

using namespace std;

int main()
{
    int i;
  cout << "Please enter an integer value: ";
  cin >> i;
  cout << "The value you entered is " << i;
  cout << " and its double is " << i*2 << ".\n";
  return 0;
  
    int marks=0;
    string input= " ";
    int temp=0;
    
  
   do {
        	marks=0;
			cout<<"Enter Student Marks"<<"\n";
			
			for (int i=0; i<5; i++)
			{
			    cout<<"Subject#"<<i+1<< " :  " ;
			    cin>>temp;
                marks+=temp;
			}
			
			cout<<"Total Marks of this Student:  "<<marks<<" out of 500";
			
			cout<<"Next Student? (Y/N)  :";
			cin>>input;
		}
		while (input == "y" || input == "Y");
        
   return 0;
}

