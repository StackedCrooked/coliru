#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <regex>

using namespace std;


int main()
{
    vector<string> strs {"TX 77845","df78965-7854","er 9875"};
    regex pat ("//w{2}");
    smatch matches;
    
    for(auto s : strs)
    {
        if(regex_search(s, matches, pat))
        {
            cout << "1" << endl;
            cout << s << ":" << matches[0] << endl;
        }
    }
    
    
}
