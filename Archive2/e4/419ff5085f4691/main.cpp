#include <iostream>
using namespace std;

void smallSort(int&, int&, int&); // #1) fix declaration

int main()
{
    int num1, num2, num3;
    cout << "Please enter the first number" << endl;
    cin >> num1;
    cout << "Please enter the second number" << endl;
    cin >> num2;
    cout << "Please enter the third number" << endl;
    cin >> num3;
    cout << "Now I will sort from smallest to biggest!" << endl;

    smallSort(num1, num2, num3); // #2) fix function call
    return 0;
}

void smallSort(int& num1, int& num2, int& num3){
    if(num1 > num2)
        swap(num1, num2);
    if(num1 > num3)
        swap(num1, num3);
    if(num2 > num3)
        swap(num2, num3);

    cout << num1 << " " << num2 << " " << num3 << endl;
}