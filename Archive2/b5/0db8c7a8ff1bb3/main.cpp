#include <iostream>
#include <string>
#include <regex>

namespace
{
    using namespace std;
}

int main(int argc,char* argv[])
{
    cout << "GCC VERSION " << __GNUC__ << '.' << __GNUC_MINOR__<< endl;
    try
    {
        const regex pattern("(\\d{4})/(\\d{2})/(\\d{2})");
        const string str = "2014/11/20";
        smatch result;
        
        regex_search(str,result,pattern);
        for(const auto& match : result)
        {
            cout << match << endl;
        }
    }
    catch(const regex_error& _e)
    {
        cout << _e.what() << endl;
    }
    return 0;
}
