#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> read_timestamps( std::istream& stm, std::string prefix = "timestamp=" )
{

    const std::size_t prefix_size = prefix.size() ;

    std::vector<std::string> result ;

    std::string line ;
    while( std::getline( stm, line) ) // for each line in the file
    {
        const auto pos = line.find(prefix) ; // search for the prefix in the line
        if( pos != std::string::npos ) // if found
        {
            const auto timestamp_start = pos + prefix_size ; // the next character after the prefix

            // create a string stream which reads from the substring starting after the prefix
            std::istringstream strstm( line.substr(timestamp_start) ) ;
            std::string timestamp ;
            if( strstm >> timestamp && !timestamp.empty() ) // if a timestamp was read
                 result.push_back(timestamp) ; // add it to the result
        }
    }

    return result ;
}

int main()
{
    std::istringstream file( "blah= blah timestamp=2014-07-08T18:13:40.837Z. blah blah\n"
                             "timestamp= 2015-07-08T18:13:40.837Z. blah=blah\n"
                             "blah blah timestamp=    2016-07-08T18:13:40.837Z.\n"
                             "blah blah does not contain timestamp blah blah\n"
                             "timestamp=2017-07-08T18:13:40.837Z.") ;
    for( std::string timestamp : read_timestamps(file) ) std::cout << timestamp << '\n' ;
}
