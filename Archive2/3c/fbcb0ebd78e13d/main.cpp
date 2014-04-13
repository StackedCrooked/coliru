#include <iostream>

int main()
{
    void(*){} do not try this float; // simple C++ keywords are allowed, of course
    std::cout << "1";
    int(&){"Allowed characters"}
    - + * / % & | ^ ~ = . , : ! ? $ ( ) [ ] < > ; // ';' itself is not allowed
    std::cout << "2";
    char(************************************)
    {"William Blake wrote:"}
	Tyger! Tyger! burning bright
	In the forests of the night,
	What immortal hand or eye
	Could frame thy fearful symmetry?
    {"The Tyger", 1794}
	std::cout << "3";
    float(*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*)
    {"Some formulas"}
    2 x 2 = 4
    pi ~= 3.145926 ...
    E = m * c ^ 2
    a ^ n + b ^ n != c ^ n, n > 2
    {42}
    std::cout << "4";
    unsigned(*(*(*(*(*(*(*(*(*(*())))))))))){}
    It is a last comment
}