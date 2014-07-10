#include<iostream>
using std::cout;
using std::endl;

struct data_member
{
    data_member(){ cout << "data_member\n"; }
    ~data_member(){ cout << "~data_member\n"; }
};

struct Y
{
    static data_member m;
    Y(){ cout << "Y\n"; }
    ~Y(){ cout << "~Y\n"; }
};

data_member Y::m;

Y y; 

int main() {} 