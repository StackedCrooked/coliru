#include <iostream>
#include <string>
#include <bitset>
#include <sstream>

using namespace std;
int main(){
    string binary_str("11001111");
bitset<8> set(binary_str);    
   std::stringstream ss;
int number;
ss << hex << set.to_ulong() << endl;
ss >> number;

std::cout << number;
}