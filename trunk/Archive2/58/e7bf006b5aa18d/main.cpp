#include<iostream>

using namespace std;
int main()
{
    float guess = 64;
    float b = 2 ; 
    if(b*b==guess)
    { cout<<"right guess"<<endl;}
    else
    {
        while(b*b !=guess)
        {
            b=( b+ (guess/b))/2;
            cout<<"the guess is "<<b<<endl;
        };
    }
    
    return 0;
    
}