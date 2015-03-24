#include <iostream>
using namespace std;

void getData(int*& data)
{
   delete[] data;
   data = new int[50];
   cout << "In getData: " << data << endl;
}

void wrap_getData(int* data) 
{
     cout << "In wrap_getData: " << data << endl;
     getData(data);
}
void call_wrapper()
{
	int *x = new int[5];
	cout << "In call_wrapper before execution: " << x << endl;
    wrap_getData(x);
    cout << "In call_wrapper after execution: " << x << endl;
}

int main()
{
	call_wrapper();
}