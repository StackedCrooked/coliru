#include <regex>
#include <string>
#include <iostream>

int main()
{
    using namespace std;

string str = "    1     10      0       11        3       11";
regex rx("\\d");

vector<int> index_matches; // results saved here 
                           // (should be {2, 8}, but always get only {2})
   
for(auto it = std::sregex_iterator(str.begin(), str.end(), rx); it != std::sregex_iterator(); ++it)
    index_matches.push_back(it->position());

for(int n: index_matches)
{
    std::cout << n << '\n';
}
}