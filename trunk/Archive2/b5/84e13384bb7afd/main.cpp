#include <iostream>
using namespace std;

int main()
{
    float number =  9999.0;
	float taxednumber = number  * (float)(20/100.0);
	taxednumber = number - taxednumber;
	cout<< taxednumber <<endl;
}