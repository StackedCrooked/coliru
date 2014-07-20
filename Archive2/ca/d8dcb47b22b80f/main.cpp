#include <iostream>
#include <string>
#include <regex>
#include <sstream>

void parse(const std::string & text,std::vector<float>& numbers,char& op)
{
    std::string tmp;
    std::stringstream stream(text);
    while (stream >> tmp)
    {
        if (std::regex_match (tmp, std::regex("^-?\\d+(\\.\\d+)?$") )){
            numbers.push_back(std::stof(tmp));
        }
        else
            op=tmp[0];
    }
}

int main ()
{
    std::string text="3.34 -5 +";
    //std::getline(std::cin,text);

    std::vector<float> numbers;
    char op;

    parse(text,numbers,op);

    std::cout<<"Numbers : ";
    for(auto i:numbers)
        std::cout<<i<<" ";
    std::cout<<"\nOperator : "<<op;

    return 0;
}
