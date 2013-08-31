#include <boost/any.hpp>
#include <functional>
#include <string>
#include <map>
#include <iostream>

typedef std::map<std::string, std::function<void(boost::any)>> Setters;

void setLocalPort(int n)
{
    std::cout << "Setting local port to " << n << std::endl;    
}

void setRemotePort(short n)
{
    std::cout << "Setting remote port to " << n << std::endl;    
}

void test()
{
    Setters setters;
    setters["LocalPort"] = [](boost::any x) { setLocalPort(boost::any_cast<int>(x)); }; 
    setters["RemotePort"] = [](boost::any x) { setRemotePort(boost::any_cast<short>(x)); }; // error prone, short should be deduced from setRemotePort's signature.
    
    setters["LocalPort"](1);
    setters["RemotePort"](2); // throws because int != short
}

int main()
{
    try
    {
        test();
    }
    catch (const std::exception& exc)
    {
        std::cout << exc.what() << std::endl;
    }
}