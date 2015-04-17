#include <iostream>
#include <vector>
#include <map>
#include <string>


int main()
{

    std::map<std::string, std::string> m = {
       {"INF_MIN", "0"},
       {"0", "1"},
       {"1", "2"},
       {"2", "3"},
	   {"3", "4"},
       {"4", "5"},
	   {"5", "6"},
	   {"6", "7"},
	   {"7", "8"},
	   {"8", "9"},
	   {"9", "INF_MAX"}
    };
 
    for(auto p: m)
        if (p.first == "INF_MIN") {
            std::cout << p.first << ' ' << p.second << '\n';    
        } else {
            std::cout << "1";
        }
        

}