#include <iostream>
#include <string>

std::string version;

void setVersion(std::string&& ver)
{
    if (ver.size()>1)
    {
        version.swap(ver);
        std::cout << "version now " << version << std::endl;
    }
}

std::string getVersion() {
    return "version2";
}

int main(){
    setVersion("version1");
    setVersion(getVersion());
    const std::string v3 = "version3";
    // doesn't work: const lvalue
    // setVersion(v3);
}