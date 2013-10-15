#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string sAssocVal = "test1, test2, test3";

    istringstream ss( sAssocVal );

    vector<string> words;
    string token;
    while( std::getline(ss, token, ',') )
    {
        words.push_back( token );
    }

    for(size_t i = 0; i<words.size(); i++){
        std::string st= words[i];
        std::cout << st << std::endl;
    }
}
