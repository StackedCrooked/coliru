#include <regex>
#include <iostream>

static bool ismatch(const std::string pattern,const std::string field)
{

        try
        {
                std::regex re(pattern);
                if(std::regex_match(field.begin(),field.end(),re))
                        return true;

                return false;
        }
        catch(std::regex_error &err)
        {
                std::cerr<<"code:"<< err.code()<<" Error: "<<err.what()<<std::endl;
                return false;
        }

}


int main()
{
        if(ismatch("^[a-zA-Z]+","on"))
        {
                std::cout<<"Yes I know";
        }else
        {
                std::cout<<"No";
        }
}
