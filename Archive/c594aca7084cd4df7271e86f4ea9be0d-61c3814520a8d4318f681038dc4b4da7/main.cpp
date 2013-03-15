#include <boost/exception/all.hpp>
#include <iostream>
#include <stdexcept>
#include <string>


// root exception type
struct ExceptionBase : virtual std::exception, virtual boost::exception { };

// error tag for suggesting probable cause or solution
typedef boost::error_info<struct Suggestion, std::string> SuggestionTag;


namespace FileSystem {        
    
struct FileSystemError : virtual ExceptionBase {};
struct FileNotFound : virtual FileSystemError {};
typedef boost::error_info<struct Info, std::string> InfoTag;

typedef boost::error_info<struct FileName, std::string> FileNameTag;

bool FileExists(const std::string &)
{
    return false;
}

void MoveFile(const std::string & from, const std::string & to)
{
    BOOST_THROW_EXCEPTION(FileNotFound() << FileNameTag(from));
}

} // namespace FileSystem

namespace Distribution {

void PublishFile(const std::string & file)
{
    std::string remote_location = "network://path/to/destination";
    try
    {
        FileSystem::MoveFile(remote_location, file);
    }    
    catch (ExceptionBase & exc)
    {
        exc << SuggestionTag("Check if the network drive is available.");
        throw;
    }
}

} // namespace Distribution


int main()
{
    try
    {
        Distribution::PublishFile("report.odt");
    }
    catch (...)
    {
        std::cerr << boost::current_exception_diagnostic_information() << std::endl;
    }
}