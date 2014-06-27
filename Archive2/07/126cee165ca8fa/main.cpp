#include <iostream>
#include <stdexcept>


struct Exception : virtual std::exception
{
    Exception(const std::string& name) : name_(name) {}
    
    const char* what() const throw() { return name_.c_str(); }
    
    std::string name_;
};


struct RuntimeError : virtual Exception
{
    RuntimeError() : Exception("RuntimeError") {}
};


struct FatalError : virtual Exception
{
    FatalError() : Exception("FatalError") {}
};


struct FileNotFound : RuntimeError
{
    FileNotFound(const std::string&) :
        Exception("FileNotFound")
    {
    }
};

struct OutOfMemory : RuntimeError, FatalError
{
    OutOfMemory() :
        Exception("OutOfMemory")
    {
    }
};


int main()
{
    try
    {
        throw FileNotFound("filename");
    }
    catch (const FatalError& e)
    {
        std::cout << "FatalError: " << e.what() << std::endl;
    }
    catch (const RuntimeError& e)
    {
        std::cout << "RuntimeError: " << e.what() << std::endl;
    }
    try
    {
        throw OutOfMemory();
    }
    catch (const FatalError& e)
    {
        std::cout << "FatalError: " << e.what() << std::endl;
    }
    catch (const RuntimeError& e)
    {
        std::cout << "RuntimeError: " << e.what() << std::endl;
    }
}