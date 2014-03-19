#include <iostream>
using namespace std;
//-------------------------------------------------

void DegreesToFarenheit()
{
     //Declaration
    float Degrees, Farenheit;

    //User Prompt
    cout << "Please Enter a Temperature in Degrees: " << endl;
    cin >> Degrees;
    cout << "" << endl;
    cout << "" << endl;

    //Program
    Farenheit = (((Degrees * 9)/5) + 32);
    cout << Degrees << " Degrees" << " is " << Farenheit << " Farenheit";
    cout << "" << endl;

}
char RepeatPrompt()
{
    char Ans;
    cout << "Would you like to enter a new value? ";
    cin >> Ans;
    cout << "" << endl;
    if(Ans = "y" or "Y")
        {DegreesToFarenheit();}
    else if(Ans = "n" or "N")
        {return 0;}
    else
        {main();}
}

int main()
{
    cout << "Degrees To Farenheit Converter V1.0" << endl;
    cout << "----------------------------------------" << endl;
    DegreesToFarenheit() ;
    RepeatPrompt() ;
    return 0;
}