#include <iostream>
using namespace std;
struct CAT
{
    CAT(){cout<<"CAT()"<<endl;}
    ~CAT(){}
};

int main()
{
    CAT c1, c2;
    CAT c3(c1); //should print out a warning?
}