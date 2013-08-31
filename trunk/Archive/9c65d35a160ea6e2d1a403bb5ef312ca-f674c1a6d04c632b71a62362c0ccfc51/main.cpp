#include<cstdio>

using namespace std;

void GetDigits(int n, int& sum, int& mul)
{
    sum = 0;
    mul = 1;
    while(n)
    {
        sum += n % 10;
        mul *= (n % 10);
        n /= 10;
    }    
}

float GetDecimal(int n)
{
    int lastDigit = n & 10;
    int sum = 0;
    while(n)
    {
           sum += sum % 10; 
    }
    sum += lastDigit / 10;
    return sum;
}

void Serie (int n)
{
    float num = 5.2;
    int num2 = 0;
    int sum,mul;
    while(n)
    {        
       GetDigits((int)(num * 10),sum,mul);
       num2 = mul + sum;
       
       n % 2 == 1 ? printf("%f\n",num) : printf("%d\n", num2);
       num = GetDecimal(num2);
       
    n--;
    }
}

int main()
{
   Serie(5);
}
