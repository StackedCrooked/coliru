#include <iostream>
#include <string>

using namespace std;

int main(){
    std::string &str = string("abc");
    std::cout << str.size();
    return 0;
}