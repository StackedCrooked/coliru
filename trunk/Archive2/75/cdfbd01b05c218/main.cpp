#include <unordered_map>
#include <utility>

struct X
{
    typedef std::unordered_map<std::string, int> Foo;
    typedef std::unordered_map<std::string, Foo> FooContainer;
    
    FooContainer bar;
    
    Foo GetSubmap(std::string name)
    {
        /*auto it = bar.find(name);
        if(it != bar.end())
        {
            return it->second;
        }else
        {
            throw "not found";
        }*/
        return bar[name];
    }
};

int main()
{
    X::Foo my_map;
    my_map["a"] = 0;
    my_map["b"] = 1;
    my_map["c"] = 2;
    my_map["d"] = 3;
    my_map["e"] = 4;
    
    X x;
    x.bar["first"] = std::move(my_map);
    
    auto result = x.GetSubmap("first");
}