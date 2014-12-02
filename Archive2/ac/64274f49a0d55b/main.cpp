#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <boost/current_function.hpp>
#include <boost/foreach.hpp>

class A{
    public:
    void myfunc1(int a, int b){
        calls[BOOST_CURRENT_FUNCTION]++;
    }
    void myfunc2(){
        calls[BOOST_CURRENT_FUNCTION]++;
    }
    std::string report_calls(){
        std::stringstream sstr;
        typedef std::pair<std::string,int> map_entry;
        BOOST_FOREACH( map_entry entry, calls)
        {
            sstr << entry.first << "=" << entry.second << std::endl;
        }
        return sstr.str();
    }
    std::map<std::string,int> calls;
};

int main()
{
    A obj;
    obj.myfunc1(0,0);
    obj.myfunc1(0,0);
    obj.myfunc2();
    std::cout<<obj.report_calls();
}
