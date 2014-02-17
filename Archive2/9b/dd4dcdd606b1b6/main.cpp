#include <iostream>
#include <vector>
#include <string>

using namespace std;                //This means that you no longer have to write std:: for anything in the std class
//using std::cout;                  //This means that you no longer have to write std:: for the usage of cout

void some_function()
{
    vector<string> K{"X","Y","Z"};
    vector<string> Y{"x","y","z"};
    vector<string> YYY(3);
    
    for(int R = 0; R < 3; ++R)
    {
        YYY[R] = K[R] + " equals " + Y[R];
    }
    
    for(int R = 0; R < 3; ++R)
    {
        cout << YYY[R] << endl;     //You have end1 (with a literal "one") here, it should be endl (with a literal letter "l", which stands for "endline")
    }                               //Place your brackets clearer and cleaner
}

int main()                          //Changed from mainfunction()
{                                   //Place your brackets clearer and cleaner
    some_function();
}
