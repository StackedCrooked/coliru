#include <iostream>


using namespace std;

void warten(unsigned int mseconds)
{
clock_t goal = mseconds + clock();
while (goal > clock());
}

int main()
{
cout << "Hello World" << endl;
warten(1000);
return 0;
}