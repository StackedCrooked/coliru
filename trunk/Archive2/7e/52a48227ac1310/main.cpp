#include <iostream>
using namespace std;

int main()
{
int myFirstNumber = 9;
int mySecondNumber = -8;
if (myFirstNumber < 0)
{
    int firstno = (myFirstNumber*-1);
}
else
{
int firstno = (myFirstNumber*1);
}
if (mySecondNumber < 0)
{
    int secno = (mySecondNumber*-1);
}
else
{
    int secno = (mySecondNumber*1);
}
if (firstno == secno)
{printf("Yes!");
}
else
{printf("No.");
return 0;
}