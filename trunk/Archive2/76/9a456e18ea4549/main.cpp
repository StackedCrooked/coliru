#include <iostream>
#include <iterator>
#include <string>
#include <regex>
 
using namespace std;
 
int main()
{
    
        string line = "(1/2)-(1/3) = (1/6)";
        //line += "(1/2 ) - (1/3) = (1/6)\0";
        //line += "(1/2) - (1/3)=(1/6)\0";
        //line += "(1/2)-(1/3)=(1/6)\0";
        //std::regex e("^\\((.+)\\).+\\((.+)\\).+\\(.+\\)$");
        //std::cmatch cm;
        std::regex reg("^\\((.+)\\).+",std::regex_constants::extended | std::regex_constants::ECMAScript);

        if(std::regex_match (line,reg))
            std::cout << "string object matched" << endl;

        if(std::regex_match( line.begin(), line.end(), reg))
            std::cout << "range matched" << endl;

        cout << "search : " << std::regex_search(line,reg) << endl;

        std::smatch sm; // same as std::match_results<string::const_iterator> sm;
        std::regex_match(line,sm,reg);
        std::cout << "string object with " << sm.size() << " matches\n";
        cout << sm[0] << endl;
        cout << sm[1] << endl;
        cout << sm[2] << endl;
        cout << sm[3] << endl;
    
}