#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
 
int main()
{
    std::string v = "abcd abcd";
    std::string t1 = "b";
 
    std::string::const_iterator result = std::find_end(v.begin(), v.end(), t1.begin(), t1.end());
    if (result == v.end()) {
        std::cout << "subsequence not found\n";
    } else {
        std::cout << "last subsequence is at: "
                  << std::distance<std::string::const_iterator>(v.begin(), result) << "\n";
    }
    return 0;
}
