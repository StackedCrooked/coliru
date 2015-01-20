#include <iostream>

using namespace std;

template<class T>
T mathAdd(T x, T y)
{
    T temp;
    temp = x + y;
    return temp;
}

int main()
{
    cout << "Running function mathAdd(), "mathAdd(8,7) << endl;  
	return 0;
}