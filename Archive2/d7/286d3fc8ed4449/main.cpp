#include <iostream>
#include <limits>
#include <stdio.h>
#include <string.h>
#include <map>
#include <functional>
using namespace std;

struct Serial;
struct Visitor;

using PathMap = map<string, std::function<void(const string&, Serial&, Visitor&)>>;

struct Serializer
{
    static PathMap paths;
};

struct Visitor
{
    template<typename T>
    void visit(const string& path, T&& something)
    {
        cout << path << " => " << something << endl;
    }
};

template<typename T, typename F>
T default_for(F fun, const char* path)
{
    Serializer::paths[path] = std::move(fun);
    return T{};
}

#define ADDPARAM(name, path, type)\
    type name = default_for<type>(  \
        [](const string& p, Serial& s, Visitor& v){ \
            v.visit(p, s.name); }, path);


struct Serial
{
    ADDPARAM(flap, "ala.destra.flap", double)
    ADDPARAM(rocket, "chassis.rocket", string)
};

PathMap Serializer::paths{};

int main()
{
    Serial s;
    s.flap = 10;
    s.rocket = "missile";
    
    Visitor v;
    for(auto& path : Serializer::paths)
    {
        path.second(path.first, s, v);
    }
}
