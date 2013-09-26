#include <iostream>
#include <iomanip>
#include <cstring>
 
std::string xfrm(std::string const& input)
{
std::string result(1+std::strxfrm(nullptr, input.c_str(), 0), '\0');
std::strxfrm(&result[0], input.c_str(), result.size());
 
return result;
}
 
int main()
{
using namespace std;
setlocale(LC_ALL, "es_ES.UTF-8");
 
const string aba = "aba";
const string rabano = "rábano";
 
cout << "Without xfrm: " << aba << " in " << rabano << " == " <<
boolalpha << (string::npos != rabano.find(aba)) << "\n";
 
cout << "Using xfrm: " << aba << " in " << rabano << " == " <<
boolalpha << (string::npos != xfrm(rabano).find(xfrm(aba))) << "\n";
}