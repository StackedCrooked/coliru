#include <boost/regex.hpp>
#include <iostream>

using namespace std;

int main(){
    string reg = "[a-zA-Z0-9]";
    boost::regex expression(reg);
    cout<<"OK"<<endl;
}