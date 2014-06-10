#include <string>
#include <iostream>
using namespace std;


const char* dosth() { return "hey"; }

int main(){
    string s1 = dosth();
    string s2 (dosth());
    string s3 {dosth()};
    auto   s4 = (string)dosth();
    
    cout << s1 << " " << s2 << " " << s3 << " " << s4 << endl;
}