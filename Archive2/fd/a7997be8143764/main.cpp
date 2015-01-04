#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <list>
#include <map>
#include <string>
using namespace std;

list<string> format(string fmt)
{
    list<string> types;
    for(auto it = fmt.begin(); it != fmt.end() && it+1 != fmt.end(); ++it)
    {
        if(*it == '%')
        {
            switch(*++it)
            {
                case 'f': types.emplace_back("real_t"); break;
                case 's': types.emplace_back("string"); break;
                case 'd': types.emplace_back("int"); break;
                case 'x': types.emplace_back("hex<int>"); break;
                case '#': types.emplace_back("delimopt"); break;
                default:
                    throw std::exception();
            }
        }
    }
    return types;
}

list<pair<string, string>> fmts = {
    //{ "objs", "" },
    //{ "tobj", "" },
    { "weap", "%d %s %s %s %d %f" },
    { "hier", "%d %s %s" },
    { "anim", "%d %s %s %s %f %d" },
    { "cars", "%d %s %s %s %s %s %s %s %d %d %x %d %f %f %# %d" },
    { "peds", "%d %s %s %s %s %s %x %x %s %d %d %s %s %s" },
    { "path", "" },
    //{ "2dfx", "" },
    { "txdp", "%s %s" },
};


int main()
{
    for(auto& pair : fmts)
    {
        bool first = true;
        auto types = format(pair.second);
        cout << "using " << pair.first << "_type" << " = ";
        cout << "data_slice<";
        for(auto& t : types)
        {
            if(first) first = false;
            else cout << ", ";
            cout << t;
        }
        cout << ">;;\n";
        
    }
}
