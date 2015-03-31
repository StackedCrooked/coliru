#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split( const std::string& p_pcstStr, char delim )  {
    std::vector<std::string> tokens;
    std::stringstream   mySstream( p_pcstStr );
    std::string         temp;

    while( getline( mySstream, temp, delim ) ) {
        tokens.push_back( temp );
    }

    return tokens;
}

int main() {
    std::string currentline = "My Name is tttt";
    std::vector<std::string>  result = split(currentline,' ');
    
    std::cout << result.size();
}