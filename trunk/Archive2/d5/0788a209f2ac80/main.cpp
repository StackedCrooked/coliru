#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
using std::cout;
using std::endl;

int main(){
      string input = "IDIOSYNCRASY";
      find_length(input);
      return 0;
}

int StringLen(char *input){

    cout<<("%s\n", input);
    int length = 0;
    while(input[length]!='\0')  //  remove ;
    {
        length++;
        cout<<("%i\n", length);
    }
}