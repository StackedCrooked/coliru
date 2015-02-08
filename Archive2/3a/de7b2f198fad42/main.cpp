#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
 using namespace std;

#include <set>
#include <iterator>

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        typedef std::set<string> SubstringSet;
        SubstringSet result;
        for(string::size_type pos = 0; pos + 10 < s.size(); ++pos) {
            auto sub = s.substr(pos, 10);
            if (string::npos != s.find(sub, pos + 1)) {
                result.insert(std::move(sub));
            }
        }
        
        /*
        vector<string> r;
        r.reserve(result.size());
        for(auto& val : result) {
            r.push_back(std::move(val));
        }
        return r;
        */
        return vector<string>(std::move_iterator<SubstringSet::iterator>(result.begin()),
                              std::move_iterator<SubstringSet::iterator>(result.end()));
    }
};

int main()
{
    std::string s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
    auto result = Solution().findRepeatedDnaSequences(s);
    for(const auto& val : result) {
        std::cout << val << ' ';
    }
}