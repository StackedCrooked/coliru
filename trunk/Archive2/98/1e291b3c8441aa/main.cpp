#include <iostream>
#include <string>
#include <vector>

void permute(std::string str, std::string app)
{
    if(str.length() == 0)
    {
        if(app.length() >0)
        {
            std::cout<<app<<std::endl;
        }
    }
    for(unsigned int i=0; i<str.length(); i++)
    {
        char l = str[i];
        std::string str2 = str;
        str2.erase(i,1);
        std::string app2 = app;
        app2.append(1,l);
        permute(str2, app2);
    }
}


int main()
{
    permute("abcd","");
}
