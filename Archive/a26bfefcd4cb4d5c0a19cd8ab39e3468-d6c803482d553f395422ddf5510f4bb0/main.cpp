#include <map>
#include <string>
#include <iostream>
int main()
{
    double doubleValue = 20;
    std::string s = "string";
    std::map<std::string, double> *th = new std::map<std::string,double>();
    th->insert(std::make_pair(s, doubleValue));
    std::cout << th->begin()->first << " " << (*th->begin()).second << std::endl;
}
