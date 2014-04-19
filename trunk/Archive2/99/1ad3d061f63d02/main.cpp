#include <map>
#include <iostream>
#include <string>

static  std::map<std::string, std::map<std::string, std::string>>  _ScalingMapVolume = {{"AA", {{"busy_timeout", "test"}}},{"BB", {{"cache_size", "10000"}}}};

int main()
{
    std::cout << _ScalingMapVolume["AA"]["busy_timeout"] << '\n';
}
