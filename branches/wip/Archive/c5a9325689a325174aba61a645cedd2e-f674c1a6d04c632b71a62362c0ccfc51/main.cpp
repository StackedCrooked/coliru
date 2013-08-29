#include <iostream>
using namespace std;

void pr ()
{
    cout << "sth";
}

int main()
{

pr;
cout << pr;  // output: 1
cout << *pr; // output: 1
cout << &pr; // output: 1

}