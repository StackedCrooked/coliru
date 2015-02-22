#include <vector>
#include <string>
#include <sstream>
#include <iostream>

std::vector<std::string> get_tokens(const std::string& line)
{
    std::vector<std::string> tokens ;
    std::string item ;
    std::stringstream ss(line);
    std::getline(ss, item, '\t');
    tokens.push_back(item);
    std::getline(ss, item, '\t');
    tokens.push_back(item);
    std::getline(ss, item, '\t');
    tokens.push_back(item);
    std::getline(ss, item, '\t');
    tokens.push_back(item);
    std::getline(ss, item, '\t');
    tokens.push_back(item);
    std::getline(ss, item);
    tokens.push_back(item);
    return tokens;
}

struct MyClass 
{
    std::string a, b ;
    int c ;
    std::string d ;
    bool e ;
    std::string f ;
};

MyClass generate_instance(const std::vector<std::string>& tokens)
{
    MyClass ret ;
    std::string::size_type sv ;
    ret.a = tokens[0];
    ret.b = tokens[1];
    ret.c = std::stoi(tokens[2], &sv);
    ret.d = tokens[3];
    ret.e = (tokens[4] == "true" ? true : false);
    ret.f = tokens[5];
    return ret ;
}

int main()
{
    std::string line1 = "aa\tbb\t123\tcc\ttrue\tdd ee\n"; // notice the space in the last token.
    std::string line2 = "AA\tBB\t123\tCC\tfalse\tDD EE\n";
    std::string line ;
    MyClass ob ;
    std::string file = line1 + line2 ; // let file contain two lines of data.
    std::stringstream input{file};
    while(std::getline(input, line))
    {
        ob = generate_instance(get_tokens(line));
        std::cout << ob.a << " " << ob.b << " " << ob.c << " " << ob.d << " " << ob.e << " " << ob.f << std::endl ;
    }
    return 0;
}