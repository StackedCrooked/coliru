#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
        vector<vector<string> > groups;
        vector<string> ret;
        
        if (strs.size() <= 1) return ret;
        
        for (string &s : strs) {
            for (vector<string> &group : groups) {
                if (isAnagram(group[0], s)) {
                    group.push_back(s);
                    break;
                }
            }
        }
        
        for (vector<vector<string> >::iterator i = groups.begin(); i != groups.end(); ++i) {
            cout << "got group: " << (*i)[0] << endl;
            if (i->size() <= 1) {
                i = groups.erase(i);
            }
        }
        
        
        for (vector<string> &group : groups) {
            ret.insert(ret.end(), group.begin(), group.end());
        }
        
        return ret;
    }
    
    bool isAnagram(string &str1, string &str2) {
        string tempStr(str2);
        
        cout << "anagram?: " << str1 << " " << tempStr << endl;
        
        for (unsigned long i = 0; i < str1.length(); ++i) {
            unsigned long pos = tempStr.find(str1[i]);
            if (pos == string::npos) {
                return false;
            }
            else {
                tempStr.erase(pos, 1);
            }
        }
        
        return true;
    }
};

int main()
{
   Solution sol;
   
   vector<string> strs{ "cat", "tac", "dog", "ddd" };
   
   vector<string> ret = sol.anagrams(strs);
   
   cout << "Test" << endl;
   
   for (string &str : ret) {
       cout << str << endl;
   }
   
   return 0;
}
