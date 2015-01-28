#include <string>
#include <iostream>
using namespace std;
 
struct foo {
    operator const std::string()
    { return "hatsjekiedee"; }
};
 
int main(){
    std::string s;
    s = foo().operator const std::string();
    cout << s << endl;
}
