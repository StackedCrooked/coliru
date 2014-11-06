#include <iostream>
//#include <conio.h>
#include <fstream>
#define in_file "input.txt"
#define out_file "output.txt"
using namespace std;

void mulitple (int, int&);

void main()
{
    ifstream ins;
    ofstream outs;
    ins.open (in_file);
    outs.open (out_file);
    int n, result;
    ins >> n;
    outs << "------------" << endl;
    outs << n;

    multiple(n, result);
    if (result = 7)
        outs << n << "is a multiple of 7" << endl;
    if (result = 11)
        outs << n << "is a multiple of 11" << endl;
    if (result = 13)
        outs << n << "is a mulitple of 13" << endl;
//    _getch();

}

void multiple(int number, int& result)
{
    ifstream ins;
    ofstream outs;
    ins.open (in_file);
    outs.open (out_file);

    ins >> number;
    if (number % 7 == 0)
        result = 7;
        else if (number % 11 == 0)
            result = 11;
            else if (number % 13 == 0)
                result = 13;
}