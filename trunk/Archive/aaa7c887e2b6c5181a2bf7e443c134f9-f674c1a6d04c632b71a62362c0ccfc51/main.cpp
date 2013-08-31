#include <boost/any.hpp>
#include <functional>
#include <string>
#include <map>
#include <iostream>

typedef std::map<std::string, std::function<void(boost::any)>> Setters;


void setRemotePort(int n)
{
    std::cout << "Setting remote port to " << n << std::endl;    
}

void setLocalPort(short n)
{
    std::cout << "Setting local port to " << n << std::endl;    
}

int main()
{
    Setters setters;
    setters["RemotePort"] = [](boost::any x) { setRemotePort(boost::any_cast<int>(x)); };
    setters["LocalPort"] = [](boost::any x) { setLocalPort(boost::any_cast<int>(x)); };
    
    setters["LocalPort"](1);
    setters["RemotePort"](2); // crash want int != short
}
