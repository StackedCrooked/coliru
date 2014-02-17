#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::endl;
using std::cout;


void some_function()
{
    vector<string> K{"X","Y","Z"};
    vector<string> Y{"x","y","z"};
    vector<string> YYY(3);
    
    for(int R = 0; R < 3; ++R){
        YYY[R] = K[R] + " equals " + Y[R];
    }
    for(int R = 0; R < 3; ++R){
        cout << YYY[R] << end1; }
}

int mainfunction(){
    some_function();
}
