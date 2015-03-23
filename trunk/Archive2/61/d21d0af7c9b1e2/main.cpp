#include <iostream>
using namespace std;

void getData(int*& data)
{
   cout << "In getData: " << data << endl;
}

void wrap_getData(int* data) 
{
     cout << "In wrap_getData: " << data << endl;
     getData(data);
}
void call_wrapper()
{
	int x;
	cout << "In call_wrapper: " << &x << endl;
    wrap_getData(&x);
}

int main()
{
	call_wrapper();
}