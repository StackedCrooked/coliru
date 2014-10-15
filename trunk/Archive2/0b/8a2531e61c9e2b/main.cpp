#include <iostream>
#include <string>

std::string version;


void setVersion(std::string&& ver)
{
    if (ver.size()>1)
    {
        version = std::move(ver);
        std::cout << "version now " << version << std::endl;
    }
}

void setVersion(std::string& ver)
{
    setVersion(std::move(ver));
}

std::string getVersion() {
    return "version2";
}

int main(){
    std::string v1 = "version0";
    setVersion(v1);
    setVersion("version1");
    setVersion(getVersion());
    const std::string v3 = "version3";
    // doesn't work: const lvalue
    // setVersion(v3);
}