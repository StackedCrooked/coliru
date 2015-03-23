#include <iostream>
using namespace std;

void getData(int*& data)
{
   delete[] data;
   data = new int[50];
   data[0] = 5;
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
    x[0] = 4; x[4] = 3;
	cout << "In call_wrapper: " << x << endl;
    wrap_getData(x);
    cout << "In call_wrapper: " << x << endl;
    cout << x[0] << endl;
}

int main()
{
	call_wrapper();
}