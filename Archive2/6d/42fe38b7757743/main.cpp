#include <iostream>
#include <string.h>

using namespace std;

double vvod (double a1, double a2, double a3) {
 
// a1=a a2=b a3=c
 
    cout<<"Введите значение коэфицента a: ";
   cin>>a1;
    cout<<endl;
	cout<<"Введите значение коэфицента b: ";
	cin>>a2;
	cout<<endl;
	cout<<"Введите значение коэфицента c: ";
	cin>>a3;
	cout<<endl;
	return (a1);
	return (a2);
	return (a3);
}

double get_result[3];

double get()
{
	double getter;
	get_result[0] = *(&getter-3);
	get_result[1] = *(&getter-1);
	get_result[2] = *(&getter-2);
}

int main() {
    memset(get_result, 0, sizeof (get_result));	
	vvod(666,42,13);
	get();
	std::cout << get_result[0] << ',' << get_result[1] << ',' << get_result[2] << '\n';
	return 0;
}