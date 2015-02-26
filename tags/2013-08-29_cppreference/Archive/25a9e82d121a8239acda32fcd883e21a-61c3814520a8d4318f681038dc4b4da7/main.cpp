#include <boost/exception/all.hpp>
#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <cxxabi.h>


template<typename T>
std::string demangle() noexcept /* terminate on throw (fair deal) */
{
    int st;
    char * const p = abi::__cxa_demangle(typeid(T).name(), 0, 0, &st);
    switch (st)
    {
        case 0: return std::unique_ptr<char, decltype(&std::free)>(p, std::free).get();
        case -1: assert(!"A memory allocation failure occurred."); // no memory = game over
        case -2: assert(!"Not a valid name under the GCC C++ ABI mangling rules.");
        case -3: assert(!"One of the arguments is invalid.");
        default: assert(!"Unexpected demangle status");
    }        
}


struct ExceptionBase : virtual std::exception, virtual boost::exception { };


namespace FileSystem {        
    
    
struct Exception : virtual ExceptionBase {};

struct FileNotFound : virtual FileSystem::Exception
{
    FileNotFound(const std::string & fileName)
    {
        *this << boost::errinfo_file_name(fileName);
    }
};
    

bool FileExists(const std::string &) { return false; }


void MoveFile(const std::string & from, const std::string & to)
{
    if (!FileExists(from))
    {
        BOOST_THROW_EXCEPTION(FileNotFound(from));
    }        
    
    /* move file */
}


} // namespace FileSystem



int main()
{
    try
    {
        FileSystem::MoveFile("source.txt", "destination.txt");
    }
    catch (...)
    {
        std::cerr << boost::current_exception_diagnostic_information() << std::endl;
    }
}