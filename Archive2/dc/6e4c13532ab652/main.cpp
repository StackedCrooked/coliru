using namespace std;
#include <iostream>

void my_function(int a, int b)
{
cout << a;
cout << b;
}

int main()
{
int a(0);
my_function(++a, a++);
cout << a;
}