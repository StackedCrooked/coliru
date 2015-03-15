#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>
#include <future>

bool match( std::string line, std::string server_name, std::string user_name )
{
    static const std::string number = "\\d+" ;
    
    // see: http://en.cppreference.com/w/cpp/regex/ecmascript 
    // (beginning of line),server_name,number,number,user_name, ... (end of line)
    const std::regex pattern( '^' + server_name + ',' + number + ',' + number + ',' + user_name + ",.+$" ) ;
    
    // http://en.cppreference.com/w/cpp/regex/regex_match
    return std::regex_match( line, pattern ) ;
}


std::vector<std::string> filter_lines( std::string logfile_name, std::string server_name, std::string user_name )
{
    std::vector<std::string> result ;

    std::ifstream file(logfile_name) ;
    std::string line ;
    while( std::getline( file, line ) ) if( match( line, server_name, user_name ) ) result.push_back(line) ;

    return result ;
}

int main()
{
    const std::string server_name = "XY" ;
    const std::string user_name = "ABCDEF" ;
    
    // http://en.cppreference.com/w/cpp/thread/future
    using future_type = std::future< std::vector<std::string> > ;
    std::vector<future_type> futures ;
    
    // 
    for( std::string logfile_name : { "a.log", "b.log", "c.log", "d.log", "e.log" } )
        futures.push_back( std::async( std::launch::async, filter_lines, logfile_name, server_name, user_name ) ) ;
        // http://en.cppreference.com/w/cpp/thread/async

    std::vector<std::string> log_records ;
    for( auto& future : futures )
    {
        // http://en.cppreference.com/w/cpp/thread/future/get
        auto vec = future.get() ; // note: get waits for async operation to complete
        
        log_records.insert( log_records.end(), vec.begin(), vec.end() ) ;
    }

    // if needed, sort vector log_records
    // print contents of vector log_records
}
