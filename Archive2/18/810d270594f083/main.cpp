#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void calculate(float a, float b, char op);

int main() {

    float answer;
    float a, b;
    char op;
    char replay;
    do{
        cout<<"Choose your operation: +, -, /, *, ^, %" <<endl;
        cin>>op;
        cout<<"Input your first number:"<<endl;
        cin>>a;
        cout<<"Input your second number:"<<endl;
        cin>>b;
        calculate(a, b, op);    
        cout<<"The answer is:"<<answer<<endl;
        cout<<"Calculate again? Y = Yes, N = No"<<endl;
        cin>>replay;
    } while ((replay == 'y' || replay == 'Y')); 
    cout<<"Thanks for using the calculator, bye!"<<endl;
    return 0;   
}

void calculate(float a, float b, char op)
{
    float answer;
    switch(op)
    {
        case '-':
            answer = a - b;
            break;
        case '+':
            answer = a + b;
            break;
        case '*':
            answer = a * b;
            break;
        case '/':
            answer = a / b;
            break;
        case '^':
            answer = pow(a, b);
            break; 
        case '%':
            answer = fmod(a, b);
            break; 
        default:
            cout<<"You did something wrong!"<<endl; 
            break;
    }

}