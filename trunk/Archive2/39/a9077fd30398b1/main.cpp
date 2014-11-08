#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <map>

#include <tr1/functional>

class AP
{
public:
    AP() : _essid("my ssid!"), _key(0) {}
    int key() { return _key; }
    std::string essid() { return _essid; }
private:
    std::string _essid;
    int _key;
};

class Wireless
{
public:
    Wireless() : _key(0)
    {
        AP ap;
        _aps.push_back(ap);
    }
    int key() { return _key; }
    AP &ap(int index) { return _aps[index]; }
private:
    std::vector<AP> _aps;
    int _key;
};

class Config
{
public:
    typedef std::string (*FnPtr)(void);

    Config() : _ip("10.0.0.1")
    {
        Wireless wireless;
        _wireless.push_back(wireless);
    }

    Wireless &wireless(int index) { return _wireless[index]; }
    std::string ip() { return _ip; }
private:
    std::vector<Wireless> _wireless;
    std::string _ip;
};



void compute(const std::string &cmd, Config &config)
{
    std::map<std::string, std::tr1::function<std::string()> > fn_map;
    fn_map["ip"] = std::tr1::bind(&Config::ip, config);

    std::cout << fn_map[cmd]() << std::endl;
}

int main(int argc, char* argv[])
{
    Config config;
    std::string cmd = "ip";

    compute(cmd, config);

    return 0;
}
