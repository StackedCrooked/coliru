#include <stdio.h>
#include <cstdlib> 
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main(){
    std::string num ("1.0");
    //std::string num ("1.1");
    cout<< std::setprecision(1) << atof(num.c_str());
    return 0;
}