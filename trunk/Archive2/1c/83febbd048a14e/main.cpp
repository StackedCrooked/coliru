#include <iostream>
using namespace std;

struct Fraction 
{
friend istream &operator>>( istream &, Fraction &);

private:
    signed int numo; // fraction numerator
    signed int deno; // fraction denomenator
    char ch; // the '/' character
};
istream &operator>>( istream &input, Fraction fraction)
{
    input >> fraction.numo;
    input >> fraction.ch;
    input >>fraction.deno;

    return input; 
}