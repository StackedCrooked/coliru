#include <boost/variant.hpp>
#include <map>
#include <string>


using namespace std;
using namespace boost;


struct Node
{    
    template<typename T>
    void set(string key, const T& value)
    {
        children_[key] = value;
    }
    
    template<typename T>
    T get(string key) const
    {
        auto it = children_.find(key);
        if (it == children_.end())
        {
            return T(); // or throw
        }
        
        return boost::get<T>(it->second); // will throw if type is wrong
    }
    
private:
    using Union = variant<int, bool, double, string, recursive_variant_>;
    map<string, Union> children_;
};


void Set(Node& node, string string, int value)
{
    node.set(string, value);
}

void Set(Node& node, string key, string text);
void Set(Node& node, string key, const Node& child);

void Get(const Node&, string, Node& out);
void Get(const Node&, string, bool& out);
void Get(const Node&, string, int& out);
void Get(const Node&, string, string& out);

