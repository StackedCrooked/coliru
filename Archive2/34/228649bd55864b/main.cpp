#include <iostream>
#include <vector>
using namespace std;

int main()
{
    string s1 = "bob"; 
    string s2 = "hey";
    string s3 = "joe";
    string s4 = "doe";
    
    vector<string> myVec;
    
    myVec.push_back(s1);
    myVec.push_back(s2);
    myVec.push_back(s3);
    myVec.push_back(s4);
    
    for (auto it = myVec.begin(), end = myVec.end(); it != end; ++it)
    {
        for (auto it2 = myVec.begin(); it2 != (it + 1); ++it2)
        {  
            std::cout << *it2 << " ";
        }
        std::cout << "\n";
    }
}
