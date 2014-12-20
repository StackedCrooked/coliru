#include <iostream>
#include <string>
using namespace std;

void t(string *s){
    s[1]='l';
}
int main(){
    string s = "HL";
    t(&s);
    cout<<s;
}