// This program develops the product of two 3-digit integers, without using calculator.

#include<iostream>
#include<cstdlib>
using namespace std;

int main()
{
    int x, y, a, b, c, answer1, answer2, answer3, finalanswer; 
    
    //a = first digit, b = second digit, c = third digit

    cout << "Give me two 3-digit integers to multiply" << endl;
    cin >> x >> y;
 
    
    cout << "Here is the calculation: \n" << endl;
 
    cout << "     " << x << endl;
    cout << "x    " << y << endl;
    
    cout << "_ _ _ _ _ \n" << endl;
   
    
    a = y/1%10;
    b = y/10%10;
    c = y/100%10;
    

    answer1 = x * a;
    answer2 = x * b;
    answer3 = x * c;
    finalanswer = x * y;
    
    cout << "    "  << answer1 << endl;
    cout << "   " << answer2 << endl;
    cout << "  " << answer3 << endl;
    
    cout << "_ _ _ _ _ \n" << endl;
    
    cout << "  " << finalanswer << endl;


    system("pause");
}