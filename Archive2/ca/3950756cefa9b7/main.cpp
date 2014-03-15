#include <iostream>
using namespace std;


int *method()
{
  int object = 10;
  return &object;
}


int main()
{
    int *object2 = method();

    cout << *object2;
}