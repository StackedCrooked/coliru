#include <iostream>
#include <regex>

using namespace std;

int main()
{
    string str = "this is\nmy multiline\r\nstring";
    regex re("^[st].*");
    
    regex linere("\\r?\\n");
    for (auto tit = sregex_token_iterator(str.begin(), str.end(), linere, -1); tit != sregex_token_iterator(); ++tit)
    {
        smatch m;
        cout << string(tit->first, tit->second) << "\t" << regex_match(tit->first, tit->second, m, re) << endl;
    }
    return 0;
}
