#include <iostream>
#include <cmath>
using namespace std;

//Write a program that asks the user to type an integer N and that indicates if N is a prime number or not .

int m, n, t,rem;

int main(){
    cout << "Enter the natural number "<< '\n' ;
    cin >> m ;
    if (m=1,m=2) 
    {
        cout << m << "is prime" << '\n' ;
    } else
    {
        for (int i; i<m; i++) 
        {
            for (n=2; n<m ; n++) 
            {
                    rem=i%n;  
            }
            if (rem == 0)
            {
                break;
            }
            cout<< i;
        }
    }
    return 0 ;
}
