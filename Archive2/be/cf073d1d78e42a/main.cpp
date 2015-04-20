#include <string>
#include <iostream>
#include <vector>

using namespace std;
int main()
{
    string s1 = "4xILASs5dmhcexwgWLIf6MJiKuA";
    string s2 = "4XILASs5dmhcexwgWLIf6MJiKuA"; // second char to UPPER (differs from s1)
    
    std::vector<std::string> list;
    list.push_back(s1);
    for(unsigned int i=0; i<list.size(); i++)
    {
        if(s2.compare(list[i]) == 0)
        {
            cout << "found" << endl;
            break;
        }
        
        if(i==list.size()-1 && s2.compare(list[i]) != 0)
            cout << "not found" << endl;
    }
}
